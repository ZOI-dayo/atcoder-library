#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../common/util.hpp"
#include "../../common/print.hpp"
#include "../../datastructure/segment-tree.hpp"

signed main() {
  io_setup();
  int N, Q;
  cin >> N >> Q;

  vec<int> a(N);
  cin >> a;
  SegmentTree<int> seg(a, 0, [](int a, int b) { return a + b; });

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
