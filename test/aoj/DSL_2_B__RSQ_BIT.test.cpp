#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include "../../datastructure/bit.hpp"

int main() {
  int n, q;
  cin >> n >> q;
  BIT<int> bit(n);
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    x--;
    if (com == 0) {
      bit.add(x, y);
    } else {
      y--;
      cout << bit.sum(y) - bit.sum(x - 1) << endl;
    }
  }
}
