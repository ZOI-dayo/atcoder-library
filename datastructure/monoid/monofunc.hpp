#pragma once

#include "./monoid.hpp"

template <class Type, MonoidConcept Mono> class Monofunc {
public:
  Monofunc() = default;
  using T = Type;
  using M = Mono;
  using MT = typename M::T;
  virtual T id() const = 0;
  virtual MT apply(T a, MT b) const = 0;
  virtual T merge(T before, T after) const = 0;
};

template <class M>
concept MonofuncConcept = requires(M &x, typename M::T before,
                                   typename M::T after, typename M::MT mono) {
  typename M::T;
  typename M::M;
  typename M::MT;
  { x.id() } -> std::same_as<typename M::T>;
  { x.apply(before, mono) } -> std::same_as<typename M::MT>;
  { x.merge(before, after) } -> std::same_as<typename M::T>;
};
