#pragma once

#include "monoids.hpp"
#include "monofunc.hpp"

namespace Monofuncs {

template <MonoidConcept M>
class RangeSetMonofunc : public Monofunc<optional<typename M::T>, M> {
public:
  using T = optional<typename M::T>;
  using MT = typename M::T;
  // using T = optional<Type>;
  // using M = Monoids::SumMonoid<T>;
  T id() { return nullopt; }
  MT apply(T a, MT b) { return a ? a : b; }
  T merge(T before, T after) { return after ? after : before; }
};
}
