#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_A"

#include "../../math/pow.hpp"

signed main() {
  int n, k;
  cin >> n >> k;
  cout << mod_pow(k, n, 1'000'000'007) << endl;
}
