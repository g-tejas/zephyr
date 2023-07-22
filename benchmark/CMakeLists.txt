cmake_minimum_required(VERSION 3.22)
project(zephyr_benchmark)

# Add the path to the main.cpp file
set(SOURCES
    src/asio_echo_client.cpp
    src/asio_echo_server.cpp
    )

# Fetch and make asio available
include(FetchContent)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio
    GIT_TAG f70f65ae54351c209c3a24704624144bfe8e70a3
)
message(STATUS "Fetching asio")
FetchContent_MakeAvailable(asio)
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
find_package(Threads)
target_link_libraries(asio INTERFACE Threads::Threads)

add_executable(asio_client src/asio_echo_client.cpp)
add_executable(asio_server src/asio_echo_server.cpp)
target_link_libraries(asio_client asio)
target_link_libraries(asio_server asio)