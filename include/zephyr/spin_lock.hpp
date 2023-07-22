#ifndef ZEPHYR_SPIN_LOCK_HPP_
#define ZEPHYR_SPIN_LOCK_HPP_

#include "zephyr/hardware_interference_size.hpp"

#include <atomic>

namespace ze {
    /*
     * @brief A spin lock implementation by Erik Rigtop (https://rigtorp.se/spinlock/)
     * However, there's a popular forum post by Linux Torvalds about how spin locks shouldn't
     * be used in the user-space. (https://www.realworldtech.com/forum/?threadid=189711&curpostid=189723)
     * The gist is that: Using spin locks in user-space can lead to unpredictable latencies
     * and contention issues because user-space threads can be involuntarily scheduled out by the OS
     * while holding the lock after using up their time slice, causing other threads to spin
     * unnecessarily.
     * */
    struct alignas(hardware_constructive_interference_size) spin_lock {
        std::atomic<bool> m_lock alignas(hardware_constructive_interference_size) = {false};

        /*
         * Attempt to acquire the mutex. Otherwise, busy wait (spin) until it is available.
         * */
        inline void lock() noexcept {
            while (true) {
                // Optimistically assume the lock is free on the first try
                if (!m_lock.exchange(true, std::memory_order_acquire)) { return; }

                // Wait for the lock to be released without generating cache misses
                while (m_lock.load(std::memory_order_relaxed)) {
                    // Issue X86 PAUSE or ARM YIELD instruction to reduce contention between
                    // hyper-threads
                    __builtin_ia32_pause();
                }
            }
        }

        /*
         * Attempt to acquire the mutex, but unlike lock() it does not wait on failure
         *
         * @return true if the lock was acquired, false otherwise.
         * */
        inline bool try_lock() noexcept {
            // First do a relaxed load to check if lock is free in order to prevent
            // unecessary cache misses if someone does while(!try_lock())
            return !m_lock.load(std::memory_order_relaxed) &&
                    !m_lock.exchange(true, std::memory_order_acquire);
        }

        /*
         * Releases the mutex
         * */
        inline void unlock() noexcept {
            m_lock.store(false, std::memory_order_release);
        }
    };
} // namespace ze

#endif // ZEPHYR_SPIN_LOCK_HPP_