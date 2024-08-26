#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/5/ALDS1_5_D"

#include "../../common/template.hpp"
#include "../../util/inversion-num.hpp"

// 転倒数
signed main() {
  io_setup();
  int n;
  cin >> n;
  vec<int> a(n);
  cin >> a;
  cout << inversion_num(a) << endl;
}
