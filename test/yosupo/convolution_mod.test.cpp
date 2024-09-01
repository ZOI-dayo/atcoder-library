#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../common/templates.hpp"

using mint = mint998;

signed main() {
  io_setup();
  int N, M;
  cin >> N >> M;
  vec<mint> a(N), b(M);
  cin >> a >> b;
  convolution(a, b);
  for (auto x : a)
    cout << x << " ";
}
