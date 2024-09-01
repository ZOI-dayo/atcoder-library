#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../math/factorial.hpp"

signed main() {
  io_setup();
  int T;
  cin >> T;
  rep(t, T) {
    int N;
    cin >> N;
    cout << fact998(N) << endl;
  }
}
