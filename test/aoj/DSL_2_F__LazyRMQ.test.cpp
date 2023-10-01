#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F"

#include "../../datastructure/lazy-segment-tree.hpp"

signed main() {
  int n, q;
  cin >> n >> q;
  LazySegtree<int, int> seg = LazySegmentTree<int, int>(
      n, (1LL << 31) - 1, -1, [](int a, int b) { return min(a, b); },
      [](int fn, int val) { return fn >= 0 ? fn : val; },
      [](int next, int current) { return next >= 0 ? next : current; });
  rep(i, q) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      seg.set(s, t + 1, x);
    } else {
      int s, t;
      cin >> s >> t;
      cout << seg.query(s, t + 1) << endl;
    }
  }
}