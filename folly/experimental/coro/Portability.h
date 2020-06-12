#include <experimental/coroutine>

namespace folly::experimental::coro {

#if _MSC_VER

using std::experimental::coroutine_handle;

struct noop_task {
  struct promise_type {
    noop_task get_return_object() noexcept {
      return { coroutine_handle<promise_type>::from_promise(*this) };
    }
    void unhandled_exception() noexcept {}
    void return_void() noexcept {}
    std::experimental::suspend_always initial_suspend() noexcept { return {}; }
    std::experimental::suspend_never final_suspend() noexcept { return {}; }
  };
  coroutine_handle<> coro;
};

coroutine_handle<> noop_coroutine() {
  return []() -> noop_task { co_return; }().coro;
}

#else

using std::experimental::noop_coroutine;

#endif
}