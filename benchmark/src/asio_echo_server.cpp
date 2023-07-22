#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "asio.hpp"

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket) : m_data(65534), m_writing(false), m_socket(std::move(socket)) {}

    void start() {
        do_read();
    }
private:
    void do_write(std::size_t length) {
        auto self(shared_from_this());
        asio::async_write(
                m_socket, asio::buffer(m_data.data(), length),
                [this, self](std::error_code ec, auto) mutable {
                    if (!ec) { do_read(); }
                    else { abort(); }
                });
    }

    void do_read() {
        auto self(shared_from_this());
        m_socket.async_read_some(
                asio::buffer(m_data.data(), m_data.size()),
                [this, self](std::error_code ec, auto length) mutable {
                    if (!ec) { do_write(length); }
                });
    }
    std::vector<char> m_data;
    bool m_writing;
    tcp::socket m_socket;
};

class Server {
public:
    Server(asio::io_context& io_context, short port) : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)){
        do_accept();
    }
private:
    void do_accept() {
        m_acceptor.async_accept([this](std::error_code ec, tcp::socket socket) {
           if (!ec) { std::make_shared<Session>(std::move(socket))->start(); }
           do_accept(); // Recursively call.
        });
    }
    tcp::acceptor m_acceptor;
};

int main(int argc, const char** argv) {
    if (argc != 2) {
        std::cout << "Please provide a port to listen on \n" << std::endl;
        return 1;
    }

    auto port = std::stoi(argv[1]);
    std::vector<std::jthread> threads;

    try {
        asio::io_context io_context;
        Server s(io_context, port);

        auto hc = std::thread::hardware_concurrency();
        if (!hc) { hc = 1; }

        for (auto i = 0u; i < hc; i++) {
            threads.emplace_back([&io_context]() { io_context.run(); });
        }

        for (auto& t : threads) {
            if (t.joinable()) { t.join(); }
        }
    } catch (std::exception &e) {
        std::cerr << "An exception: " << e.what() << "\n" << std::endl;
    }

    return 0;

}