#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/8/ITP2/5/ITP2_5_D"

#include "../../common/templates.hpp"

signed main() {
  io_setup();
  int n;
  cin >> n;
  rep_perm(n, [&](vec<int> v) {
    transform<int>(v, [](int &val) { val++; });
    join_out(cout, v);
  });
}
