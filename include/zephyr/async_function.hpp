#ifndef ZEPHYR_ASYNC_FUNCTION_HPP_
#define ZEPHYR_ASYNC_FUNCTION_HPP_

#include <coroutine>

namespace ze {
    namespace impl {
        template <typename Base>
        concept Execution = requires(Base a) {
            // Compound requirements within require expression. These functions should be invoke-able and
            // the return type must be the same respectively, as shown.
            { a.initial_suspend() } noexcept -> std::same_as<std::suspend_never>;
            { a.final_suspend() } noexcept -> std::same_as<std::suspend_never>;
            { a.return_void() } noexcept -> std::same_as<void>;
            { a.get_return_object()} noexcept -> std::same_as<std::coroutine_handle<Base>>;
        };
    }; // namespace Details

    template<impl::Execution PromiseType = execution_promise>
    class async_function {
    public:
        // Handle for the coroutine
        using coro_handle = std::coroutine_handle<PromiseType>;

        async_function(coro_handle) {}
        ~async_function() = default;
        async_function(const async_function&) = delete;
        async_function& operator=(const async_function& rhs) = delete;
        async_function(async_function&&) = delete;
        async_function& operator=(async_function&& rhs) = delete;

    };
} // namespace ze

#endif // ZEPHYR_ASYNC_FUNCTION_HPP_
