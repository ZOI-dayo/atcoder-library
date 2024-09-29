#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B"

#include "../../common/templates.hpp"

signed main() {
  io_setup();
  int n, q;
  cin >> n >> q;
  WUF<int> wuf(n);
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      int z;
      cin >> z;
      wuf.merge(x, y, z);
    } else {
      if (wuf.same(x, y))
        cout << wuf.diff(x, y) << endl;
      else
        cout << "?" << endl;
    }
  }
}
