#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../datastructure/segment-tree.hpp"

signed main() {
  io_setup();
  int N, Q;
  cin >> N >> Q;

  struct Monoid {
    using T = ll;
    static T e() { return 0; }
    static T op(T a, T b) { return a + b; }
  };

  Segtree<Monoid> seg(N);
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
