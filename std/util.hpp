#pragma once

#include <algorithm>
#include <numeric>
#include "concepts.hpp"

namespace zoi {
namespace util {

// 可変引数min
template <class... T> auto min(const T... a) {
  return std::min(std::initializer_list<std::common_type_t<T...>>{a...});
}

// 可変引数max
template <class... T> auto max(const T... a) {
  return std::max(std::initializer_list<std::common_type_t<T...>>{a...});
}

template <class T> bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}
template <class T> bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return 1;
  }
  return 0;
}

// 合計値を求める
template <concepts::iterable C, concepts::addable T > T sum(const C &c) { return std::reduce(c.begin(), c.end()); }

// 二分探索
template <typename T, concepts::lambda<bool, T> F>
inline T bin_search(T ok, T ng, const F is_ok) {
  assert(is_ok(ok));
  assert(!is_ok(ng));
  assert(ok < ng);
  while (abs(ok - ng) > 1) {
    T mid = (ok + ng) / 2;
    if (is_ok(mid))
      ok = mid;
    else
      ng = mid;
  }
  return ok;
}

template<std::integral T>
T sign(T x) {
  return x < 0 ? -1 : x > 0 ? 1 : 0;
}

template<std::integral T>
T ceil(T x, T base) {
  assert(base != 0);
  return (x + base - 1) / base;
}

// 負の数も考えて
template<std::integral T>
T floor(T x, T base) {
  assert(base != 0);
  if(-sign(x) == sign(base)) {
    return (x - base + 1) / base;
  }
  return x / base;
}

}
}
