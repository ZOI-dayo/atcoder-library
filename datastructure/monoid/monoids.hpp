#pragma once

#include "monoid.hpp"

namespace Monoids {

template <addable T = int> struct SumMonoid : public Monoid<T> {
  T e() const override { return T(0); }
  T op(T a, T b) const override { return a + b; }
};

template <integral T = int> struct MinMonoid : public Monoid<T> {
  T e() const override { return numeric_limits<T>::max(); }
  T op(T a, T b) const override { return min(a, b); }
};

template <integral T = int> struct MaxMonoid : public Monoid<T> {
  T e() const override { return numeric_limits<T>::min(); }
  T op(T a, T b) const override { return max(a, b); }
};

} // namespace Monoids
