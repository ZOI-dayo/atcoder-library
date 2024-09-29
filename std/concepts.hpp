#pragma once

#include <concepts>
#include <iterator>

namespace zoi {
  namespace concepts {

    template <class T>
    concept iterable = requires(T& x) {
      x.begin();
      x.end();
    };

    template <class T>
    concept addable = requires(T& x, T& y) {
      { x + y } -> std::convertible_to<T>;
    };

    template <typename F, typename R, typename... Args>
    concept lambda = std::invocable<F, Args...> &&
                     std::same_as<std::invoke_result_t<F, Args...>, R>;

  } // namespace concepts
} // namespace zoi
