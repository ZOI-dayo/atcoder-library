//@yosupo unionfind

#include "../../../all.hpp"

void solve() {
  int n, q;
  fin >> n >> q;
  UnionFind uf(n);
  while(q--) {
    int t, u, v;
    fin >> t >> u >> v;
    if(t == 0) {
      uf.merge(u, v);
    } else {
      fout << (int) uf.same(u, v) << '\n';
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