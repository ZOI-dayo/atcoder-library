#pragma once

#include "../common/alias.hpp"

// 繰り返し2乗法
template <integral T, integral F> constexpr T pow(T a, T n) {
  T ans = 1;
  while (n > 0) {
    if (n & 1)
      ans *= a;
    a *= a;
    n >>= 1;
  }
  return ans;
}

template <integral T, integral F> constexpr T mod_pow(T a, F n, const ll mod) {
  T ans = 1;
  while (n > 0) {
    if (n & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return ans;
}
