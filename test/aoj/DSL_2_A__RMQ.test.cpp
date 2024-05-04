#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include "../../datastructure/segment-tree.hpp"

signed main() {
  io_setup();
  int n, q;
  cin >> n >> q;
  SegmentTree<int32_t> seg(
    n, numeric_limits<int32_t>::max(),
    [](int32_t a, int32_t b) { return min(a, b); }
  );
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
