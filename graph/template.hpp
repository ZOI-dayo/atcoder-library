#pragma once

#include "../common/template.hpp"

// Node
template <class T = ll> struct WeightedNode {
  int id;
  T cost;
  WeightedNode(int id, T cost) : id(id), cost(cost) {}
};

struct WeightState {
public:
  int location;
  ll used_cost;
  WeightState(int location, ll used_cost)
      : location(location), used_cost(used_cost) {}
  bool operator<(const WeightState &n) const { return used_cost < n.used_cost; }
  bool operator>(const WeightState &n) const { return used_cost > n.used_cost; }
};

// Graph
struct Graph {
private:
  const int n;
  vec<vec<int>> edges;

public:
  explicit Graph(int n) : n(n), edges(n) {}
  inline void add_edge(int u, int v, bool directed = false) {
    edges[u].emplace_back(v);
    if (directed)
      edges[v].emplace_back(u);
  }
  inline vec<int> &operator[](int i) { return edges[i]; }
  const inline int size() { return n; }
};

template <class T = ll> using WeightedGraph = vec<vec<WeightedNode<T>>>;

template <class T = ll> using WGraph = WeightedGraph<T>;
