#pragma once

#include <cstdint>
#include <limits>
#include <vector>

namespace zoi {
namespace graph {

template <class T = int64_t> struct WeightedNode {
  int id;
  T cost = std::numeric_limits<T>::max();
  WeightedNode(int id, T cost) : id(id), cost(cost) {}
};

template <class T = int64_t> struct WeightedGraph {
private:
  const int n;
  const bool directed;

public:
  std::vector<std::vector<WeightedNode<T>>> edges;
  explicit WeightedGraph(int n, bool directed = false)
      : n(n), directed(directed), edges(n) {}
  inline void add_edge(int u, int v, T w) {
    edges[u].emplace_back(WeightedNode(v, w));
    if (!directed)
      edges[v].emplace_back(WeightedNode(u, w));
  }
  inline std::vector<WeightedNode<T>> &operator[](int i) { return edges[i]; }
  inline int size() const { return n; }
};

template <class T = int64_t> using WGraph = WeightedGraph<T>;

} // namespace graph
} // namespace zoi
