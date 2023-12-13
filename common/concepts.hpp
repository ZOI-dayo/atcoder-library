#pragma once

#include "alias.hpp"

template <class T>
concept addable = requires(T a, T b) {
  { a + b } -> convertible_to<T>;
};
