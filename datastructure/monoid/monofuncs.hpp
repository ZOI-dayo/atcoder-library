#pragma once

#include "monofunc.hpp"
#include "monoids.hpp"
#include "affine.hpp"

namespace Monofuncs {

template <MonoidConcept M>
class RangeSetMonofunc : public Monofunc<optional<typename M::T>, M> {
public:
  using T = optional<typename M::T>;
  using MT = typename M::T;
  // using T = optional<Type>;
  // using M = Monoids::SumMonoid<T>;
  T id() const override { return nullopt; }
  MT apply(T a, MT b) const override { return a ? a.value() : b; }
  T merge(T before, T after) const override { return after ? after : before; }
};

template <MonoidConcept M>
class RangeAffineMonofunc : public Monofunc<Affine<typename M::T>, M> {
public:
  using MT = typename M::T;
  using T = Affine<MT>;
  // using T = pair<Type, Type>;
  // using M = Monoids::SumMonoid<T>;
  T id() const override { return T(1, 0); }
  MT apply(T a, MT b) const override { return a(b); }
  T merge(T before, T after) const override {
    return before * after;
  }
};

} // namespace Monofuncs
