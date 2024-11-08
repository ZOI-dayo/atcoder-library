#pragma once

#include "util/all.hpp"

inline int pow_mod(int x, int n, int mod) {
  int res = 1;
  while(n > 0) {
    if(n & 1) res = (ll)res * x % mod;
    x = (ll)x * x % mod;
    n >>= 1;
  }
  return res;
}
