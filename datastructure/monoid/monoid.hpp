#pragma once

#include "../../common/template.hpp"

/*
template <class M>
concept MonoidConcept = requires(M &x, M::T a, M::T b) {
  typename M::T;
  { M::e() } -> std::same_as<typename M::T>;
  { M::op(a, b) } -> std::same_as<typename M::T>;
};
*/

template <class Type> class Monoid {
public:
  Monoid() = default;
  using T = Type;
  virtual T e() const = 0;
  virtual T op(T a, T b) const = 0;
};

template <class M>
concept MonoidConcept = requires(M &x, typename M::T a, typename M::T b) {
  // derived_from<M, Monoid<typename M::T>>;
  typename M::T;
  { x.e() } -> std::same_as<typename M::T>;
  { x.op(a, b) } -> std::same_as<typename M::T>;
};
