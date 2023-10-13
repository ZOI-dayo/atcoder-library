#define PROBLEM "https://judge.yosupo.jp/problem/addition_of_big_integers"

#include "../../common/template.hpp"

signed main() {
  int T;
  cin >> T;
  rep(i, T) {
    mpz_class a, b;
    cin >> a >> b;
    cout << a + b << endl;
  }
}
