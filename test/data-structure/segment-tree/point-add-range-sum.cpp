#include "all.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vec<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  };
  SumSegmentTree<ll> st(a);
  rep(Q, q) {
    int type;
    cin >> type;
    if(type == 0) {
      int p, x;
      cin >> p >> x;
      st.set(p, st[p] + x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << st[l, r] << "\n";
    }
  }
}
