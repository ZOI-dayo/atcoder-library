#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include "../../datastructure/segment-tree.hpp"

struct RMQMonoid32 {
  using T = int32_t;
  static T e() { return numeric_limits<T>::max(); }
  static T op(T a, T b) { return min(a, b); }
};

signed main() {
  io_setup();
  int n, q;
  cin >> n >> q;
  auto seg = Segtree<RMQMonoid32>(n);
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      seg.set(x, y);
    } else {
      cout << seg.query(x, y + 1) << endl;
    }
  }
}
