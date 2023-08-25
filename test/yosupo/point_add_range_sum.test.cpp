#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../datastructure/segment-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;

  Segtree<ll> seg(N, 0, [](ll a, ll b) { return a + b; });
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
