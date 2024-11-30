#pragma once

#include "util/all.hpp"

template <typename T, typename U>
inline T powi(T x, U n) {
  T res = 1;
  while(n > 0) {
    if(n & 1) res *= x;
    x *= x;
    n >>= 1;
  }
  return res;
}

template <typename T, typename U, typename V>
inline T pow_mod(T x, U n, const V mod) {
  T res = 1;
  while(n > 0) {
    if(n & 1) res = res * x % mod;
    x = x * x % mod;
    n >>= 1;
  }
  return res;
}
