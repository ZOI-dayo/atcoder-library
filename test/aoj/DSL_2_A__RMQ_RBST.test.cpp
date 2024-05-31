#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include "../../common/util.hpp"
#include "../../datastructure/rbst.hpp"

signed main() {
  io_setup();
  int n, q;
  cin >> n >> q;
  RBST<int32_t> tree(
    numeric_limits<int32_t>::max(),
    [](int32_t a, int32_t b) { return min(a, b); });
  rep(i, n) {
    tree.insert_at(0, numeric_limits<int32_t>::max());
  }
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    if(com == 0) {
      tree.erase_at(x);
      tree.insert_at(x, y);
    } else {
      cout << tree.query(x, y + 1) << endl;
    }
  }
}
