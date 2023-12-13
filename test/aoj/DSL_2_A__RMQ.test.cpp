#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include "../../datastructure/segment-tree.hpp"
#include "../../datastructure/monoid/monoids.hpp"

signed main() {
  io_setup();
  int n, q;
  cin >> n >> q;
  auto seg = SegmentTree(n, Monoids::MinMonoid<int32_t>());
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      seg.set(x, y);
    } else {
      cout << seg.query(x, y + 1) << endl;
    }
  }
}
