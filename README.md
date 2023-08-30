<p align="center">
  <img src="resources/zephyr_icon.png" />
</p>

# zephyr

zephy is a C++ thread-per-core library that provides asynchronous I/O primitives and synchronization tools for building high-performance network applications.

Key features:
- Asynchronous I/O with io_uring
- Futures, coroutines and observables
- Synchronization primitives like mutexes and semaphores
- TCP networking - clients, servers, streams
- Timers and async signal handling
- AF_XDP support for high speed packet processing
`zephyr` applications center around an event loop which drives asynchronous logic:

```cpp
Task<int> co_echo(std::shared_ptr<io_uring>& handle) {
  void* buf;
  TcpListener listener = TcpListener();
  TcpStream stream_ = TcpStream();

  listener.bind_socket("127.0.0.1", htons(3344));
  
  listener.listen_socket(1024);

  co_await listener.async_accept(handle, &stream_);
  
  if(posix_memalign(&buf, 1024, 1024))
    co_return 1;

  while(1) {
    int n = co_await stream_.async_recv(handle, buf, 1024);

    if (n == 0) break;

    co_await stream_.async_send(handle, buf, n);
  }

  co_return 0;
}
```

## Build
```shell
git clone https://github.com/g-tejas/zephyr
cd zephyr
git submodule update --init

make # build zephyr.so
make example # build examples
```

The AF_XDP socket and BPF integration allows building high performance network functions like load balancers, firewalls, NATs etc without kernel involvement.

`zephyr` provides the core asynchronous infrastructure to leverage modern Linux features like io_uring, eBPF, AF_XDP for constructing fast and scalable network services in C++20.

# Ideas
- [ ] Use tracy for performance handling?

## Credits
- [Issue in zig repository for event loop redesign](https://github.com/ziglang/zig/issues/8224)
- [A Programmer-Friendly I/O Abstraction Over io_uring and kqueue](https://tigerbeetle.com/blog/a-friendly-abstraction-over-iouring-and-kqueue/)
- [⭐ AF_XDP in Glommio](https://github.com/bryandmc/glommio/blob/xdp/XDP.md)
- 