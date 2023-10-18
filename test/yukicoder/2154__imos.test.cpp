#define PROBLEM "https://yukicoder.me/problems/no/2154"

#include "../../common/template.hpp"
#include "../../datastructure/imos.hpp"

signed main() {
  io_setup();

  int N, M;
  cin >> N >> M;
  imos<ll> imos(N);
  rep(i, M) {
    int l, r;
    cin >> l >> r;
    imos.add(N-l, N-r+1, 1);
  }
  imos.build();
  rep(i, N) {
    cout << imos.get(i) << endl;
  }
}
