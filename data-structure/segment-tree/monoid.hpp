#pragma once

#include "../../util/all.hpp"

template <typename M>
concept MonoidConcept = requires(M m, M::value_type a, M::value_type b) {
{ m.op(a, b) } -> std::same_as<typename M::value_type>;
{ m.e() } -> std::same_as<typename M::value_type>;
};

template <typename T>
class SumMonoid {
public:
  using value_type = T;
  inline T op(T a, T b) {
    return a + b;
  }
  inline constexpr T e() {
    return T(0);
  }
};

template <typename T>
class MaxMonoid {
public:
  using value_type = T;
  inline T op(T a, T b) {
    return max(a, b);
  }
  inline constexpr T e() {
    return numeric_limits<T>::min();
  }
};

template <typename T>
class MinMonoid {
public:
  using value_type = T;
  inline T op(T a, T b) {
    return min(a, b);
  }
  inline constexpr T e() {
    return numeric_limits<T>::max();
  }
};
