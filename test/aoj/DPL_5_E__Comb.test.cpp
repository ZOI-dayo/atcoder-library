#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_E"

#include "../../common/template.hpp"
#include "../../math/combination.hpp"

signed main() {
  io_setup();
  int n, k;
  cin >> n >> k;
  using Cmb = Combination<1'000'000'007, 1010>;
  cout << Cmb::nCr(k, n) << endl;
}
