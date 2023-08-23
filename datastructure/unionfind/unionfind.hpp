#pragma once

#include "../../common/template.hpp"

struct UnionFind {
private:
  vec<int> _parents, _size;
public:
  explicit UnionFind(int n): _parents(n), _size(n, 1) {
    iota(all(_parents), 0);
  }
  int find(int a) {
    if(_parents[a] == a) return a;
    else return _parents[a] = find(_parents[a]);
  }
  void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if(a != b) {
      // merge後の親はa
      if(_size[a] < _size[b]) swap(a, b);
      _size[a] += _size[b];
      _parents[b] = a;
    }
  }
  bool same(int a, int b) {
    return find(a) == find(b);
  }
  int size(int a) {
    return _size[find(a)];
  }
  // vec<vec<int>> groups() {}
};
using UF = UnionFind;
