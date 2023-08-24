#pragma once

#include "../../common/template.hpp"

ll mod_pow(ll a, int n, ll mod) {
  int ans = 1;
  while (n > 0) {
    if (n & 1) ans = ans * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return ans;
}

ll pow(ll a, int n) {
  return mod_pow(a, n, numeric_limits<ll>::max());
}
