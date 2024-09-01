#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_A"

#include "../../common/template.hpp"
#include "../../datastructure/union-find.hpp"

signed main() {
  io_setup();
  int n, q;
  cin >> n >> q;
  UF uf(n);
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      uf.merge(x, y);
    } else {
      cout << uf.same(x, y) << endl;
    }
  }
}
