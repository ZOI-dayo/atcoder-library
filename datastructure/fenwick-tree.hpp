#pragma once

#include "../common/template.hpp"

template <typename T> struct FenwickTree {
private:
  T _n;
  vec<T> _data;

public:
  FenwickTree(T n) : _n(n), _data(n + 1, 0) {}
  void add(int i, T val) {
    i++;
    while (i <= _n) {
      _data[i] += val;
      i += i & -i;
    }
  }
  int sum(int i) {
    i++;
    T ans = 0;
    while (i > 0) {
      ans += _data[i];
      i -= i & -i;
    }
    return ans;
  }
};
