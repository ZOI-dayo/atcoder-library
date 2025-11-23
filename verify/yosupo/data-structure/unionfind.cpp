//@yosupo unionfind

#include "../../../all.hpp"

void solve() {
  int n, q;
  cin >> n >> q;
  UnionFind uf(n);
  while(q--) {
    int t, u, v;
    cin >> t >> u >> v;
    if(t == 0) {
      uf.merge(u, v);
    } else {
      cout << (int) uf.same(u, v) << '\n';
    }
  }
}

int main() {
  int t = 1;
//   cin >> t;
  while(t--) {
    solve();
  }
}