#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../datastructure/segment-tree.hpp"
#include "../../datastructure/monoid/monoids.hpp"

signed main() {
  io_setup();
  int N, Q;
  cin >> N >> Q;

  SegmentTree seg(N, Monoids::SumMonoid());
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
