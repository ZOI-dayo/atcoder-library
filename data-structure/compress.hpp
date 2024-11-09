#pragma once

#include "util/all.hpp"

template <typename T>
class Compress {
private:
  const int n;
  int comp_n;
  // compress: dict[i] -> i
  vec<T> dict;
  // src[i] -> comp[i]
  vec<T> compressed;

public:
  explicit Compress(const vec<T>& src): n(src.size()), comp_n(0), dict(src), compressed(n, 0) {
    sort(all(dict));
    erase(unique(all(dict)), dict.end());
    comp_n = dict.size();
    rep(i, n) compressed[i] = lower_bound(all(dict), src[i]) - dict.begin();
  }
  int size() const { return n; }
  int comp_size() const { return comp_n; }
  T operator[](int i) const { return compressed[i]; }
  int comp(T x) const { return lower_bound(all(dict), x) - dict.begin(); }
  T get(int comp_index) const { return dict[comp_index]; }
};
