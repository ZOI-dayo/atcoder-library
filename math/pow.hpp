#pragma once

#include "../common/template.hpp"

// 繰り返し2乗法
constexpr ll pow(ll a, int n) {
  ll ans = 1;
  while (n > 0) {
    if (n & 1)
      ans *= a;
    a *= a;
    n >>= 1;
  }
  return ans;
}

constexpr ll mod_pow(ll a, int n, const ll mod) {
  int ans = 1;
  while (n > 0) {
    if (n & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return ans;
}
