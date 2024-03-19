#pragma once

#include "../common/alias.hpp"
#include "../common/int128_t.hpp"

// 繰り返し2乗法
template <integral T, integral F> constexpr T pow(T a, F n) {
  T ans = 1;
  while (n > 0) {
    if (n & 1)
      ans *= a;
    a *= a;
    n >>= 1;
  }
  return ans;
}

constexpr ll powm(ll a, ll n, const ll mod) {
  lll ans = 1;
  while (n > 0) {
    if (n & 1)
      ans = ans * a % mod;
    a = ((lll)a) * a % mod;
    n >>= 1;
  }
  return ans;
}
