#pragma once

#include "../../common/template.hpp"

struct UnionFind {
private:
  vec<int> parents;
public:
  UnionFind(int n): parents(n) {
    iota(all(parents), 0);
  }
  int find(int a) {
    if(parents[a] == a) return a;
    else return parents[a] = find(parents[a]);
  }
  int merge(int a, int b) {
    a = find(a);
    b = find(b);
    if(a == b) return a;
    return parents[b] = a;
  }
  bool same(int a, int b) {
    return find(a) == find(b);
  }
  // int size(int a) {
    // return count(all(parents), find(a));
  // }
  // vec<vec<int>> groups() {}
};
using UF = UnionFind;
