#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include "../../datastructure/segment-tree.hpp"

signed main() {
  int n, q;
  cin >> n >> q;

  struct Monoid {
    using T = int;
    static T e() { return 0; }
    static T op(T a, T b) { return a + b; }
  };

  Segtree<Monoid> seg(n);
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    x--;
    if (com == 0) {
      seg.set(x, seg.get(x) + y);
    } else {
      y--;
      cout << seg.query(x, y + 1) << endl;
    }
  }
}
