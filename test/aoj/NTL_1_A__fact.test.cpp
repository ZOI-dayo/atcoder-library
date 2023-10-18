#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A"

#include "../../math/prime.hpp"

signed main() {
  io_setup();
  int n;
  cin >> n;
  cout << n << ":";
  auto primes = prime_factorize(n);
  for (auto p : primes) {
    rep(i, p.exp) cout << " " << p.prime;
  }
  cout << endl;
}
