#pragma once

#include "../common/alias.hpp"
#include "modint.hpp"

template <int32_t MOD = 998244353, int32_t MAX = 100010> class Combination {
private:
  using mint = modint<MOD>;
  // static constinit const int32_t MAX = 2000010;
  constinit static const array<mint, MAX> fact;
  // static const array<mint, MAX> invfact;
public:
  constexpr Combination() = default;
  static mint nCr(int32_t n, int32_t r) {
    if (n < 0 || r < 0 || n < r)
      return 0;
    assert(n < MAX);
    return fact[n] * fact[r].inv() * fact[n - r].inv();
  }
  static mint nPr(int32_t n, int32_t r) {
    if (n < 0 || r < 0 || n < r)
      return 0;
    assert(n < MAX);
    return fact[n] * fact[n - r].inv();
  }
  static mint nHr(int32_t n, int32_t r) {
    if (n < 0 || r < 0)
      return 0;
    assert(n < MAX);
    // assert(n >= r);
    return r == 0 ? 1 : nCr(n + r - 1, r);
  }
};

template <int32_t MOD, int32_t MAX>
constinit const array<modint<MOD>, MAX> Combination<MOD, MAX>::fact = []() {
  array<Combination<MOD, MAX>::mint, MAX> fact;
  fact[0] = 1;
  for (int32_t i = 1; i < MAX; ++i)
    fact[i] = fact[i - 1] * i;
  return fact;
}();
// template <int32_t MOD>
// constinit const array<modint<MOD>, Combination<MOD>::MAX>
// Combination<MOD>::invfact = Combination<MOD>::fact | views::transform([](auto
// x){return x.inv();});
/*
template <int32_t MOD>
constinit const array<modint<MOD>, Combination<MOD>::MAX>
Combination<MOD>::invfact = [](){
  array<Combination<MOD>::mint, Combination<MOD>::MAX> invfact;
  rep(i, Combination<MOD>::MAX) invfact[i] =  fact[i].inv();
  return invfact;
}();
  */
