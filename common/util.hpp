#pragma once

#include "alias.hpp"

// --- Utils ---

// 二分探索
template <typename T>
inline T bin_search(T ok, T ng, const function<bool(T)> is_ok) {
  assert(is_ok(ok) && !is_ok(ng));
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

// 合計値を求める
ll sum(const vec<ll> &v) { return accumulate(all(v), 0LL); }

// 可変引数min
template <class... T> auto min(T... a) {
  return min(initializer_list<common_type_t<T...>>{a...});
}

// 可変引数max
template <class... T> auto max(T... a) {
  return max(initializer_list<common_type_t<T...>>{a...});
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

// 3項間不等式
// 広義単調増加
inline bool is_increasing(int x, int y, int z) { return x <= y && y <= z; }

// 半開区間[x, z)にyが含まれるか?
inline bool is_contained(int x, int y, int z) { return x <= y && y < z; }

// 頂点(x, y)が範囲に含まれるか
inline bool is_contained(int H, int W, int x, int y) {
  return is_contained(0, x, H) && is_contained(0, y, W);
}

// rootに対し、aとbが同じ側にあるか (=は含まない)
inline bool is_same_side(int root, int a, int b) {
  return (root < a) == (root < b);
}

// vector継承にする?
template <typename T> struct vec_accumulate : vec<T> {
  vec<T> data;
  explicit vec_accumulate(vec<T> &v) : data(v.size()) {
    assert(v.size() > 0);
    data[0] = v[0];
    for (int i = 1; i < v.size(); ++i)
      data[i] = data[i - 1] + v[i];
  }

  T &operator[](int i) {
    assert(is_contained(-1, i, data.size()));
    if (i == -1)
      return T();
    return data[i];
  }
};

void io_setup() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cout << std::fixed << std::setprecision(15);
}
