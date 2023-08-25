#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include "../../datastructure/segment-tree.hpp"

int main() {
  int n, q;
  cin >> n >> q;
  Segtree<int> seg(n, 0, [](int a, int b) { return a + b; });
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    x--;
    if (com == 0) {
      seg.set(x, seg.get(x) + y);
    } else {
      y--;
      cout << seg.query(x, y + 1) << endl;
    }
  }
}
