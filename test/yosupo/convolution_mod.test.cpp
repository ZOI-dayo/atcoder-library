#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../common/template.hpp"
#include "../../convolution/convolution.hpp"
#include "../../math/modint.hpp"

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
