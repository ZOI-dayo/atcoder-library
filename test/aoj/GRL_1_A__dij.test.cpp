#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A"

#include "../../common/template.hpp"
#include "../../graph/dijkstra.hpp"

signed main() {
  io_setup();
  int V, E, r;
  cin >> V >> E >> r;
  WGraph<> graph(V);
  rep(i, E) {
    int s, t, d;
    cin >> s >> t >> d;
    graph[s].emplace_back(WeightedNode(t, d));
  }
  auto result = dijkstra(graph, r);
  for (auto cost : result) {
    if (cost == INF) {
      cout << "INF" << endl;
    } else {
      cout << cost << endl;
    }
  }
}
