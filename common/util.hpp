#pragma once

#include "alias.hpp"
#include "concepts.hpp"

// --- Utils ---


// 順列全探索
inline void rep_perm(int n, function<void(vec<int> &)> f) {
  vec<int> v(n);
  iota(v.begin(), v.end(), 0);
  do {
    f(v);
  } while (next_permutation(v.begin(), v.end()));
}

inline void rep_bit(int n, function<void(int)> f) { rep(i, 1LL << n) f(i); }

// 配列 to string
template <typename T> inline string join(const vec<T> &v, string sep = " ") {
  string res = "";
  rep(i, v.size()) res += to_string(v[i]) + (i == v.size() - 1 ? "" : sep);
  return res;
}
template <typename T>
inline void join_out(ostream &os, const vec<T> &v, string sep = " ",
                     string end = "\n") {
  int n = v.size();
  rep(i, n) os << v[i] << (i == n - 1 ? end : sep);
}

template <typename T>
inline void transform(vec<T> &src, function<void(T &)> f) {
  for (auto &val : src)
    f(val);
}

// ベース指定ceil
inline ll ceil(ll x, ll base) { return (x + base - 1) / base * base; }
// ベース指定floor
inline ll floor(ll x, ll base) { return x / base * base; }


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
template <typename T> struct vec_accumulate : public vec<T> {
  explicit vec_accumulate(vec<T> &v) : vec<T>(v.size()) {
    assert(v.size() > 0);
    this->at(0) = v[0];
    for (int i = 1; i < v.size(); ++i)
      this->at(i) = this->at(i - 1) + v[i];
  }

  // [0, i]の和
  // なので、-1 <= i < size()
  T operator[](int i) {
    assert(is_contained(-1, i, this->size()));
    if (i == -1)
      return T();
    return this->at(i);
  }
};

// vector func
template <typename T> inline void unique_erase(vec<T> &v) {
  sort(all(v));
  v.erase(unique(all(v)), v.end());
}

// view

void io_setup() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cout << std::fixed << std::setprecision(15);
}
