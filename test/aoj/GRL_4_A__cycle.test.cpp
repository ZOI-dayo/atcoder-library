#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_A"

#include "../../graph/cycle.hpp"

signed main() {
  int V, E;
  cin >> V >> E;
  Graph graph(V);
  rep(i, E) {
    int s, t;
    cin >> s >> t;
    graph[s].emplace_back(t);
  }
  bool result = false;
  rep(i, V) { result |= has_cycle(graph, i); }
  cout << result << endl;
}
