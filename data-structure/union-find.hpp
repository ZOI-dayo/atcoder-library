#pragma once

#include "../util/all.hpp"

class UnionFind {
  uint n;
  vec<int> par;

public:
  UnionFind(uint n) : n(n), par(n, -1) {}

  uint find(uint x) {
    if (par[x] < 0) return x;
    return par[x] = find(par[x]);
  }

  bool same(uint x, uint y) {
    return find(x) == find(y);
  }

  void merge(uint x, uint y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (-par[x] < -par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    n--;
  }

  uint size(uint x) {
    return -par[find(x)];
  }

  uint count() {
    return n;
  }

  vv<uint> groups() {
    vv<uint> g(par.size());
    vec<uint> starts;
    rep(i, par.size()) {
      if(par[i] < 0) {
        starts.emplace_back(i);
      } else {
        g[par[i]].emplace_back(i);
      }
    }
    vv<uint> ans;
    ans.reserve(n);
    vec<uint> st;
    for(auto s : starts) {
      ans.push_back({s});
      st.emplace_back(s);
      while(!st.empty()) {
        auto v = st.back(); st.pop_back();
        ans.back().emplace_back(v);
        for(auto c : g[s]) {
          st.emplace_back(c);
        }
      }
    }
    return ans;
  }
};
