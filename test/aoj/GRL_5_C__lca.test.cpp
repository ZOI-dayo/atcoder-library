#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_C"

#include "../../graph/lca.hpp"

signed main() {
  io_setup();
  int n;
  cin >> n;
  Graph graph(n);
  rep(i, n) {
    int k;
    cin >> k;
    graph[i].resize(k);
    rep(j, k) {
      int c;
      cin >> c;
      graph[i][j] = c;
    }
  }
  LCA lca(graph);
  int q;
  cin >> q;
  rep(i, q) {
    int u, v;
    cin >> u >> v;
    cout << lca.query(u, v) << endl;
  }
}
