#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_D"

#include "../../common/template.hpp"
#include "../../math/combination.hpp"

signed main() {
  io_setup();
  int n, k;
  cin >> n >> k;
  using Cmb = Combination<1'000'000'007, 2010>;
  cout << Cmb::nCr(n+k-1, k-1) << endl;
}
