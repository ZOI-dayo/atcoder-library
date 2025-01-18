#pragma once

#include "util/all.hpp"

class Tree {
  int age = 0;
  nullable<pair<int, vec<int>>> depth_cache;
  nullable<pair<int, vec<int>>> euler_tour_cache;
  nullable<pair<int, vvec<int>>> doubling_cache;
public:
  int n;
  vec<int> parent;
  vec<vec<int>> children;
  Tree(int n) : n(n), parent(n, -1), children(n) {}
  Tree(vec<pair<int, int>> edges) : n(edges.size() + 1), parent(n, -1), children(n) {
    for(auto&& [u, v] : edges) {
      add_edge(u, v);
    }
  }

  void add_edge(int u, int v) {
    parent[v] = u;
    children[u].push_back(v);
    age++;
  }

  void dfs(int v, function<void(int)> f, function<void(int)> g) {
    f(v);
    for(auto&& u : children[v]) {
      dfs(u, f, g);
    }
    g(v);
  }

  // O(n) or O(1) (cache)
  vec<int> depth() {
    if(depth_cache.has_value() && depth_cache->first == age) {
      return depth_cache->second;
    }
    vec<int> d(n);
    int depth = 0;
    dfs(0, [&](int v) {
      depth++;
      d[v] = depth;
    }, [&](int _) {
      depth--;
    });
    depth_cache = {age, d};
    return d;
  }

  // O(n) or O(1) (cache)
  vec<int> euler_tour() {
    if(euler_tour_cache.has_value() && euler_tour_cache->first == age) {
      return euler_tour_cache->second;
    }
    vec<int> tour;
    dfs(0, [&](int v) {
      tour.push_back(v);
    }, [&](int v) {
      tour.push_back(v);
    });
    euler_tour_cache = {age, tour};
    return tour;
  }

  // O(n log n) or O(1) (cache)
  vvec<int> doubling() {
    if(doubling_cache.has_value() && doubling_cache->first == age) {
      return doubling_cache->second;
    }
    vvec<int> doubling(n, vec<int>(31, -1));
    rep(i, n) {
      doubling[i][0] = parent[i];
    }
    rep(j, 31 - 1) {
      rep(i, n) {
        if(doubling[i][j] != -1) {
          doubling[i][j + 1] = doubling[doubling[i][j]][j];
        }
      }
    }
    return doubling;
  }

  // O(log n)
  int lca(int u, int v) {
    // TODO オイラーツアー+SparseTableでO(1)にする
    vec<int> depth = this->depth();
    vvec<int> doubling = this->doubling();
    if(depth[u] > depth[v]) {
      swap(u, v);
    }
    rrep(i, 31) {
      if((depth[v] - depth[u]) >> i & 1) {
        v = doubling[v][i];
      }
    }
    if(u == v) {
      return u;
    }
    rrep(i, 31) {
      if(doubling[u][i] != doubling[v][i]) {
        u = doubling[u][i];
        v = doubling[v][i];
      }
    }
    return parent[u];
  }
};
