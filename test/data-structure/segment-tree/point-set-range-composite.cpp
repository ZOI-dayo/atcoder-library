#include "all.hpp"

using mint = modint<998'244'353>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vec<pair<mint, mint>> ab(n);
  rep(i, n) cin >> ab[i].first >> ab[i].second;
  SegmentTree<pair<mint,mint>> seg(ab, [](auto a, auto b) { return pair{a.first * b.first, a.second * b.first + b.second};}, {1, 0});
  rep(Q, q) {
    int type;
    cin >> type;
    if(type == 0) {
      int p, c, d;
      cin >> p >> c >> d;
      seg.set(p, {c, d});
    } else {
      int l, r, x;
      cin >> l >> r >> x;
      auto [c, d] = seg[l, r];
      cout << c * x + d << '\n';
    }
  }
}
