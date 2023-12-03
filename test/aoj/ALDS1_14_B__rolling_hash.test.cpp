#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/14/ALDS1_14_B"

#include "../../string/rolling-hash.hpp"

signed main() {
  io_setup();
  string t, p;
  cin >> t >> p;
  using RH = RollingHash<1000000007>;
  using RHS = RollingHashedString<1000000007>;
  auto t_rhs = RHS(t), p_rhs = RHS(p);
  rep(i, (int)t.size() - (int)p.size() + 1) {
    if (t_rhs.query(i, i + p.size()).hash == p_rhs.query(0, p.size()).hash) {
      cout << i << endl;
    }
  }
}
