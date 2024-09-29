#define PROBLEM "https://yukicoder.me/problems/no/789"

#include "../../common/templates.hpp"

signed main() {
  io_setup();
  int N;
  cin >> N;

  DynamicSegmentTree<int> seg(1'000'000'001, 0,
                              [](int a, int b) { return a + b; });
  int ans = 0;
  rep(i, N) {
    int type;
    cin >> type;
    if (type == 0) {
      int x, y;
      cin >> x >> y;
      seg.set(x, seg.get(x) + y);
    } else {
      int l, r;
      cin >> l >> r;
      ans += seg.query(l, r + 1);
    }
  }
  cout << ans << endl;
}
