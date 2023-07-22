cmake_minimum_required(VERSION 3.22)
project(zephyr
    LANGUAGES CXX
    DESCRIPTION "Hyper-fast io_uring backed event loop"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-DRELEASE -O3 -g")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

option(BUILD_TESTS "Build zephyr tests" ON)
option(BUILD_EXAMPLES "Build zephyr examples" ON)

include(build_helpers)

add_library(${PROJECT_NAME} STATIC src/event_loop.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC
    -fcoroutines
    -pthread
    -Wall
    -Wextra
    -g)

target_include_directories(${PROJECT_NAME} PUBLIC include)

#enable_testing()
#
if(BUILD_TESTS)
    message(STATUS "Compiling tests")

    # add_zephyr_test()
endif()

if(BUILD_EXAMPLES)
    message(STATUS "Compiling examples")

    # add_zephyr_example(echo_server)
    # add_zephyr_example(logging_echo_server)

endif()

add_subdirectory(benchmark)
target_link_libraries(${PROJECT_NAME} uring)