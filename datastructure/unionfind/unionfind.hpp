#pragma once

#include "../../common/template.hpp"

struct UnionFind {
 private:
  int _n;
  vec<int> _parents;

 public:
  explicit UnionFind(int n) : _n(n), _parents(n) { iota(all(_parents), 0); }
  int find(int a) {
    if (_parents[a] == a)
      return a;
    else
      return _parents[a] = find(_parents[a]);
  }
  void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      // merge後の親はa
      _parents[b] = a;
    }
  }
  bool same(int a, int b) { return find(a) == find(b); }
  vec<vec<int>> groups() {
    vec<int> leaders(_n), group_size(_n);
    rep(i, _n) {
      leaders[i] = find(i);
      group_size[leaders[i]]++;
    }
    vec<vec<int>> res(_n);
    rep(i, _n) res[i].reserve(group_size[i]);
    rep(i, _n) res[leaders[i]].push_back(i);
    res.erase(remove_if(all(res), [&](const vec<int>& v) { return v.empty(); }),
              res.end());
    return res;
  }
};
using UF = UnionFind;
