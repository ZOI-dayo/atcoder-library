#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../../common/template.hpp"
#include "../../datastructure/fenwick-tree.hpp"

signed main() {
  io_setup();
  int N, Q;
  cin >> N >> Q;
  vec<int> a(N);
  cin >> a;

  FenwickTree<int> ft(a);

  rep(q, Q) {
    int l, r;
    cin >> l >> r;
    cout << ft.sum(l, r) << endl;
  }
}
