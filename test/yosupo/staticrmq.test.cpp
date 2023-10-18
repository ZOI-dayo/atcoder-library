#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../datastructure/segment-tree.hpp"

signed main() {
  io_setup();
  int N, Q;
  cin >> N >> Q;

  auto seg = RMQSeg(N);
  rep(i, N) {
    int a;
    cin >> a;
    seg.set(i, a);
  }

  rep(i, Q) {
    int l, r;
    cin >> l >> r;
    cout << seg.query(l, r) << endl;
  }
}
