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
  int n;
  vec<vec<int>> edges;

public:
  Graph(int n) : n(n), edges(n) {}
  void add_edge(int u, int v, bool directed = false) {
    edges[u].emplace_back(v);
    if (directed)
      edges[v].emplace_back(u);
  }
  vec<int> &operator[](int i) { return edges[i]; }
  int size() { return n; }
};

template <class T = ll> using WeightedGraph = vec<vec<WeightedNode<T>>>;

template <class T = ll> using WGraph = WeightedGraph<T>;
