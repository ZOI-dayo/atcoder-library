#include "all.hpp"

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vec<int> a(n);
  cin >> a;
  MinSegmentTree<int> st(a);
  rep(Q, q) {
    int l, r;
    cin >> l >> r;
    cout << st[l, r] << "\n";
  }
}

