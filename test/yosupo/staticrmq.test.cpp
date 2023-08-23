#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../datastructure/segment-tree/segment-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;

  Segtree<int> seg(N);
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
