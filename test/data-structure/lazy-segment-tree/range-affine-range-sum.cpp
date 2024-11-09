#include "all.hpp"

using mint = modint<998'244'353>;

int main() {
  int n, q;
  cin >> n >> q;
  vec<mint> a(n);
  cin >> a;
  LazySegmentTree<mint, pair<mint, mint>> st(
    a,
    [](auto a, auto b) { return a + b; },
    [](auto a, auto b) { return pair{a.first * b.first, a.second * b.first + b.second}; },
    [](auto f, auto x, auto len) { return f.first * x + f.second * len; },
    0,
    {1, 0}
  );
  rep(Q, q) {
    int type;
    cin >> type;
    if(type == 0) {
      int l, r, b, c;
      cin >> l >> r >> b >> c;
      st.set(l, r, {b, c});
    } else {
      int l, r;
      cin >> l >> r;
      cout << st[l, r] << "\n";
    }
  }
}
