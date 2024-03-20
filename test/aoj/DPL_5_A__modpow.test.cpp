#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_A"

#include "../../common/template.hpp"

signed main() {
  io_setup();
  int n, k;
  cin >> n >> k;
  cout << powm(k, n, 1'000'000'007) << endl;
}
