#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_A"

#include "../../common/templates.hpp"
#include "../../graph/diameter.hpp"

using namespace std;
using namespace zoi;
using namespace graph;

using ll = long long;

template <typename T> using vec = vector<T>;
template <typename T> using vvec = vec<vec<T>>;

#define rep(i, n) for (ll i = 0; i < n; ++i)

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
