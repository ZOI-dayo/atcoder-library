#pragma once

#include "../datastructure/comp.hpp"
#include "../datastructure/fenwick-tree.hpp"

int inversion_num(const vec<int> &a) {
  comp<int> c(a);

  int n = a.size();
  FenwickTree<int> bit(n);
  int ans = 0;
  rep(i, n) {
    ans += i - bit.sum(c[i]);
    bit.add(c[i], 1);
  }
  return ans;
}
