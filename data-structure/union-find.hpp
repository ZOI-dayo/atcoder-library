#pragma once

#include "util/all.hpp"

class UnionFind {
  size_t n;
  vec<size_t> par;
  vec<size_t> sz;

public:
  UnionFind(size_t n) : n(n), par(n), sz(n, 1) {
    iota(all(par), 0);
  }

  size_t find(size_t x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
  }

  bool same(size_t x, size_t y) {
    return find(x) == find(y);
  }

  void merge(size_t x, size_t y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    par[y] = x;
    sz[x] += sz[y];
  }

  size_t size(size_t x) {
    return sz[find(x)];
  }

  size_t count() {
    size_t res = 0;
    for (size_t i = 0; i < n; ++i) {
      if (par[i] == i) ++res;
    }
    return res;
  }
};
