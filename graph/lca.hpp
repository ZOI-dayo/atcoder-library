#include "depth.hpp"

struct LCA {
private:
  Graph graph;
  int root;
  // parent[k][v] := vの2^k先の親
  vec<vec<int>> parent;
  vec<TreeNodeInfo> depth_data;

public:
  LCA(Graph &graph, int root = 0) : graph(graph), root(root) {
    depth_data = depth(graph, root);
    int n = graph.size();
    int logn = 1;
    while ((1 << logn) < n)
      logn++;
    parent = vector(logn, vector(n, -1LL));
    for (int i = 0; i < n; i++)
      parent[0][i] = depth_data[i].parent;
    // ダブリング
    for (int k = 0; k + 1 < logn; k++) {
      for (int i = 0; i < n; i++) {
        if (parent[k][i] < 0)
          parent[k + 1][i] = -1;
        else
          parent[k + 1][i] = parent[k][parent[k][i]];
      }
    }
  }

  int query(int u, int v) {
    if (depth_data[u].depth > depth_data[v].depth)
      swap(u, v);
    int logn = parent.size();
    // uとvの深さが同じになるまで親を辿る
    rep(k, logn) {
      if ((depth_data[v].depth - depth_data[u].depth) >> k & 1) {
        v = parent[k][v];
      }
    }
    // にぶたん
    if (u == v)
      return u;
    for (int k = logn - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }
};
