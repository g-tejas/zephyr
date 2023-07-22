#ifndef ZEPHYR_STRONG_TYPES_HPP_
#define ZEPHYR_STRONG_TYPES_HPP_

#include <chrono>
#include <concepts>
#include <cstdint>
#include <limits>
#include <ostream>

namespace ze {

    /**
     * A struct for providing strict typing of thread ids'.
     */
    struct thread_t {

        /**
         * @brief This value signifies either no thread or any thread is allowed.
         */
        static constexpr auto ANY_THREAD = std::numeric_limits<std::uint16_t>::max() - 1;

        /**
         * @brief The logical thread ID
         */
        std::uint16_t m_thread = ANY_THREAD;

        /**
         * @brief Gets a thread_t object with its value initialised to ANY_THREAD
         *
         * @return constexpr thread_t
         */
        static constexpr thread_t any_thread() {
            return thread_t{ANY_THREAD};
        }

        /**
         * @brief Equality operator is default.
         *
         * @param _first The lhs
         * @param _second The rhs
         * @return true If equal
         * @return false If not equal
         */
        friend constexpr bool operator==(const thread_t _first, const thread_t _second) = default;

        /**
         * @brief Inequality operator is default.
         *
         * @param _first The lhs.
         * @param _second The rhs.
         * @return true If not equal
         * @return false If equal
         */
        friend constexpr bool operator!=(const thread_t _first, const thread_t _second) = default;

        /**
         * @brief 3-way operator is default for a std::strong_ordering.
         *
         * @param _first The lhs.
         * @param _second The rhs.
         */
        friend constexpr auto operator<=>(const thread_t _first, const thread_t _second) {
            return _first.m_thread <=> _second.m_thread;
        }

        /**
         * @brief 3-way operator with a std::integral for a std::strong_ordering.
         *
         * @param _first The lhs.
         * @param _second The rhs.
         */
        template <std::integral T>
        friend constexpr auto operator<=>(const thread_t _first, const T _number) {
            return _first.m_thread <=> _number;
        }

        /**
         * @brief Equality operator with a std::integral.
         *
         * @param _first The lhs
         * @param _second The rhs
         * @return true If equal
         * @return false If not equal
         */
        template <std::integral T>
        friend constexpr bool operator==(const thread_t _first, const T _second) {
            return _first.m_thread == _second;
        }

        /**
         * @brief Inequality operator with a std::integral.
         *
         * @param _first The lhs
         * @param _second The rhs
         * @return true If equal
         * @return false If not equal
         */
        template <std::integral T>
        friend constexpr bool operator!=(const thread_t& _first, const T _second) {
            return _first.m_thread != _second;
        }
    };

    /**
     * @brief Namespace for thread_t based operations
     */
    namespace thread {

        /**
         * @brief Construct a thread_t based of an id.
         *
         * @param _thread The thread id.
         * @return constexpr auto thread_t{_thread}
         */
        constexpr auto in(std::uint16_t _thread) noexcept {
            return thread_t{_thread};
        }

        /**
         * @brief Get a thread_t for any thread.
         *
         * @return constexpr auto thread_t{}
         */
        constexpr auto any() noexcept {
            return thread_t{};
        }
    }   // namespace thread

    /**
     * @brief Print the value of a thread to a stream.
     *
     * @param _os The out stream.
     * @param _thread The thread to print.
     * @return std::ostream& _os
     */
    inline std::ostream& operator<<(std::ostream& _os, const thread_t _thread) {
        _os << "thread[" << _thread.m_thread << "]";
        return _os;
    }

    /**
     * @brief A struct for providing strict typing for timing.
     */
    struct order_t {

        /**
         * @brief The amount of time in nanoseconds.
         */
        std::uint64_t m_order = 0;

        /**
         * @brief 3-way operator for a std::strong_ordering
         */
        constexpr auto operator<=>(const order_t& _other) const {
            return m_order <=> _other.m_order;
        }

        /**
         * @brief 3-way operator with a std::integral for a std::strong_ordering
         */
        template <std::integral Integral>
        constexpr auto operator<=>(const Integral _number) const {
            return m_order <=> _number;
        }

        /**
         * @brief Add two order_t's together.
         *
         * @param _lhs The lhs.
         * @param _rhs The rhs.
         * @return constexpr auto order_t{_lhs.order_ + _rhs.order_}
         */
        friend constexpr auto operator+(order_t lhs, order_t rhs) noexcept {
            return order_t{lhs.m_order + rhs.m_order};
        }

        /**
         * @brief subtract two order_t's together.
         *
         * @param _lhs The lhs.
         * @param _rhs The rhs.
         * @return constexpr auto order_t{_lhs.order_ - _rhs.order_}
         */
        friend constexpr auto operator-(order_t lhs, order_t rhs) noexcept{
            return order_t{lhs.m_order - rhs.m_order};
        }
    };

    /**
     * @brief Namespace for order_t based helper functions.
     */
    namespace order {

        /**
         * @brief Get an order_t for _number seconds.
         *
         * @param _number The number of seconds.
         * @return constexpr order_t order_t{_number * 1000000000}
         */
        inline constexpr order_t seconds(std::uint64_t _number) noexcept {
            return order_t{_number * 1000000000};
        }

        /**
         * @brief Get an order_t for _number seconds.
         *
         * @param _number The number of seconds.
         * @return constexpr order_t order_t{_number * 1000000000}
         */
        inline constexpr order_t in_seconds(std::uint64_t _number) noexcept {
            return seconds(_number);
        }

        /**
         * @brief Get an order_t for _number milliseconds.
         *
         * @param _number The number of milliseconds.
         * @return constexpr order_t order_t{_number * 1000000}
         */
        inline constexpr order_t milli(std::uint64_t _number) noexcept {
            return order_t{_number * 1000000};
        }

        /**
         * @brief Get an order_t for _number milliseconds.
         *
         * @param _number The number of milliseconds.
         * @return constexpr order_t order_t{_number * 1000000}
         */
        inline constexpr order_t in_milli(std::uint64_t _number) noexcept {
            return milli(_number);
        }

        /**
         * @brief Get an order_t that represents now.
         *
         * @return constexpr order_t order_t{};
         */
        inline constexpr order_t now() noexcept {
            return order_t{};
        }

    }   // namespace order
}   // namespace ze

#endif // ZEPHYR_STRONG_TYPES_HPP_