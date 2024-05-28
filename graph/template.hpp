#pragma once

#include "../common/template.hpp"

// Node
template <class T = ll> struct WeightedNode {
  int id;
  T cost = numeric_limits<T>::max();
  WeightedNode(int id, T cost) : id(id), cost(cost) {}
};

template <class T = ll> struct WeightState {
public:
  int location;
  T used_cost;
  WeightState(int location, T used_cost)
      : location(location), used_cost(used_cost) {}
  bool operator<(const WeightState &n) const { return used_cost < n.used_cost; }
  bool operator>(const WeightState &n) const { return used_cost > n.used_cost; }
};

// Graph
struct Graph {
private:
  const int n;
  const bool directed;
  vec<vec<int>> edges;

public:
  explicit Graph(int n, bool directed = false)
      : n(n), directed(directed), edges(n) {}
  inline void add_edge(int u, int v) {
    edges[u].emplace_back(v);
    if (!directed)
      edges[v].emplace_back(u);
  }
  inline vec<int> &operator[](int i) { return edges[i]; }
  inline int size() const { return n; }
};

template <class T = ll> struct WeightedGraph {
private:
  const int n;
  const bool directed;

public:
  vec<vec<WeightedNode<T>>> edges;
  explicit WeightedGraph(int n, bool directed = false)
      : n(n), directed(directed), edges(n) {}
  inline void add_edge(int u, int v, T w) {
    edges[u].emplace_back(WeightedNode(v, w));
    if (!directed)
      edges[v].emplace_back(WeightedNode(u, w));
  }
  inline vec<WeightedNode<T>> &operator[](int i) { return edges[i]; }
  inline int size() const { return n; }
};

// template <class T = ll> using WeightedGraph = vec<vec<WeightedNode<T>>>;

template <class T = ll> using WGraph = WeightedGraph<T>;
