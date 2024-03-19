#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"

#include "../../common/util.hpp"
#include "../../string/rolling-hash.hpp"

signed main() {
  io_setup();
  string t, p;
  cin >> t >> p;
  auto t_rhs = RollingHash(t), p_rhs = RollingHash(p);
  auto h = RollingHash("abc");
  auto h2 = RollingHash("b");
  rep(i, (int)t.size() - (int)p.size() + 1) {
    if (t_rhs.query(i, i + p.size())[0] == p_rhs.query(0, p.size())[0]) {
      cout << i << endl;
    }
  }
}
