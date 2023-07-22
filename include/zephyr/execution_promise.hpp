#ifndef ZEPHYR_EXECUTION_PROMISE_HPP_
#define ZEPHYR_EXECUTION_PROMISE_HPP_

#include <coroutine>
#include <iostream>

namespace ze {
    /**
     * @brief The simplest promise type to allow a function to behave in async manner.
     */
    class execution_promise {
    public:
        std::coroutine_handle<execution_promise> get_return_object() noexcept {
            return std::coroutine_handle<execution_promise>::from_promise(*this);
        }

        auto initial_suspend() noexcept {
            return std::suspend_never{};
        }

        auto final_suspend() noexcept {
            return std::suspend_never{};
        }

        auto return_void() noexcept {}

        void unhandled_exception() {
            // TODO: Not implemented
        }
    };

} // namespace ze

#endif // ZEPHYR_EXECUTION_PROMISE_HPP_