#pragma once

#include "../common/template.hpp"

template <typename T> struct FenwickTree {
private:
  T _n;
  vec<T> _data;

public:
  explicit FenwickTree(T n) : _n(n), _data(n + 1, 0) {}
  explicit FenwickTree(const vec<T> &src) : _n(src.size()), _data(_n+1, 0) {
    rep(i, _n) add(i, src[i]);
  }

  void add(int i, T val) {
    i++;
    while (i <= _n) {
      _data[i] += val;
      i += i & -i;
    }
  }
  // [0, i]
  int sum(int i) const {
    i++;
    T ans = 0;
    while (i > 0) {
      ans += _data[i];
      i -= i & -i;
    }
    return ans;
  }
  // [l, r)
  int sum(int l, int r) const { return sum(r - 1) - sum(l - 1); }
};
