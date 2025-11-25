#pragma once

#include "../util/all.hpp"

class UnionFind {
  int n;
  vec<int> par;

public:
  inline explicit UnionFind(int n) : n(n), par(n, -1) {}

  inline int find(int x) {
    if (par[x] < 0) return x;
    return par[x] = find(par[x]);
  }

  inline bool same(int x, int y) {
    return find(x) == find(y);
  }

  inline void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (-par[x] < -par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    n--;
  }

  inline int size(int x) {
    return -par[find(x)];
  }

  inline int count() {
    return n;
  }

  inline vv<int> groups() {
    vv<int> g(par.size());
    vec<int> starts;
    rep(i, par.size()) {
      if(par[i] < 0) {
        starts.emplace_back(i);
      } else {
        g[par[i]].emplace_back(i);
      }
    }
    vv<int> ans;
    ans.reserve(n);
    vec<int> st;
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
