#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../common/print.hpp"
#include "../../common/util.hpp"
#include "../../datastructure/dynamic-segment-tree.hpp"

signed main() {
  io_setup();
  int N, Q;
  cin >> N >> Q;

  DynamicSegmentTree<int> seg(N, 0, [](int a, int b) { return a + b; });
  rep(i, N) {
    int a;
    cin >> a;
    seg.set(i, a);
  }

  rep(i, Q) {
    int type;
    cin >> type;
    if (type == 0) {
      int p, x;
      cin >> p >> x;
      seg.set(p, seg.get(p) + x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.query(l, r) << endl;
    }
  }
}
