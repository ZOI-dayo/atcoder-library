#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../../datastructure/union-find.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;

  UF uf(N);

  rep(i, Q) {
    int t, u, v;
    cin >> t >> u >> v;
    if (t == 0) {
      uf.merge(u, v);
    } else {
      cout << uf.same(u, v) << endl;
    }
  }
}
