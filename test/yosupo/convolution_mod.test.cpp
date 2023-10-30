#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../common/template.hpp"
#include "../../convolution/ntt.hpp"
#include "../../math/modint.hpp"

// using mint = modint<998244353>;

signed main() {
  io_setup();
  int N, M;
  cin >> N >> M;
  vec<ll> a(N), b(M);
  cin >> a >> b;;
  ntt::get_instance().polymul(a, b);
  for(auto x : a) cout << x << " ";
}
