#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_A"

#include "../../common/templates.hpp"

signed main() {
  io_setup();
  int n;
  cin >> n;
  vvec<wedge_t<ll>> graph(n);
  rep(i, n - 1) {
    int s, t, w;
    cin >> s >> t >> w;
    graph[s].emplace_back(t, w);
    graph[t].emplace_back(s, w);
  }
  cout << diameter(graph) << endl;
}
