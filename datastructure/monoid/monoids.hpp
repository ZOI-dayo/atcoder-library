#pragma once

#include "monoid.hpp"

namespace Monoids {

template <integral T = int> struct SumMonoid : public Monoid<T> {
  T e() { return 0; }
  T op(T a, T b) { return a + b; }
};

template <integral T = int> struct MinMonoid : public Monoid<T> {
  T e() const override { return numeric_limits<T>::max(); }
  T op(T a, T b) const override { return min(a, b); }
};

} // namespace Monoids
