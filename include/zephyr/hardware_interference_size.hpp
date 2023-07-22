#ifndef ZEPHYR_HARDWARE_INTERFERENCE_SIZE_HPP_
#define ZEPHYR_HARDWARE_INTERFERENCE_SIZE_HPP_

#include <cstddef>

// Taken from: https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size
#ifdef __cpp_lib_hardware_interference_size
using std::hardware_constructive_interference_size;
using std::hardware_destructive_interference_size;
#else
// 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
constexpr std::size_t hardware_constructive_interference_size = 64;
constexpr std::size_t hardware_destructive_interference_size = 64;
#endif

#endif // ZEPHYR_HARDWARE_INTERFERENCE_SIZE_HPP_
