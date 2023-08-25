#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_B"

#include "../../math/pow.hpp"

int main() {
  int m, n;
  cin >> m >> n;
  cout << mod_pow(m, n, 1'000'000'007) << endl;
}
