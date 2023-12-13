#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "../../datastructure/lazy-segment-tree.hpp"
#include "../../datastructure/monoid/monofuncs.hpp"
#include "../../math/modint.hpp"

using mint = mint998;

signed main() {
  io_setup();
  int N, Q;
  cin >> N >> Q;
  vec<mint> a(N);
  cin >> a;

  LazySegmentTree<Monofuncs::RangeAffineMonofunc<Monoids::SumMonoid<mint>>> seg(
      a);

  rep(q, Q) {
    int type;
    cin >> type;
    if (type == 0) {
      int l, r, b, c;
      cin >> l >> r >> b >> c;
      seg.set(l, r, {b, c});
    } else {
      int i;
      cin >> i;
      cout << seg.get(i) << endl;
    }
  }
}
