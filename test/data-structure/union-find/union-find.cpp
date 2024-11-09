#include "all.hpp"

int main() {
  io_setup();
  int n, q;
  cin >> n >> q;
  UnionFind uf(n);
  rep(Q, q) {
    int t, u, v;
    cin >> t >> u >> v;
    if (t == 0) {
      uf.merge(u, v);
    } else {
      cout << uf.same(u, v) << '\n';
    }
  }
}
