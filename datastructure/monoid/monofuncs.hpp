#pragma once

#include "monofunc.hpp"
#include "monoids.hpp"

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
} // namespace Monofuncs
