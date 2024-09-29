#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_F"

#include "../../common/templates.hpp"

signed main() {
  io_setup();
  int n, k;
  cin >> n >> k;
  using Cmb = Combination<1'000'000'007, 1010>;
  cout << Cmb::nCr(n - 1, k - 1) << endl;
}
