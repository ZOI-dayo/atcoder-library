#define PROBLEM "https://yukicoder.me/problems/no/649"

#include "../../common/util.hpp"
#include "../../datastructure/rbst-multiset.hpp"

signed main() {
  io_setup();
  int Q, K;
  cin >> Q >> K;
  K--;
  RBSTMultiSet<int> tree;
  rep(q, Q) {
    int type;
    cin >> type;
    if (type == 1) {
      int v;
      cin >> v;
      tree.insert(v);
    } else {
      if (K >= tree.size()) {
        cout << -1 << endl;
        continue;
      }
      cout << tree.get_at(K) << endl;
      tree.erase_at(K);
    }
  }
}
