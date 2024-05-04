#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../../datastructure/lazy-segment-tree.hpp"
#include "../../datastructure/monoid/affine.hpp"
#include "../../datastructure/monoid/monofunc.hpp"
#include "../../datastructure/monoid/monoid.hpp"
#include "../../math/modint.hpp"

using mint = mint998;

signed main() {
  io_setup();
  int N, Q;
  cin >> N >> Q;

  struct Node {
    mint sum;
    int size;
    Node(mint sum, int size) : sum(sum), size(size) {}
    Node operator+(const Node &rhs) const {
      return {sum + rhs.sum, size + rhs.size};
    }
  };

  vec<Node> a(N, {0, 0});
  rep(i, N) {
    int x;
    cin >> x;
    a[i] = {x, 1};
  }

  struct M : public Monoid<Node> {
    T e() const override { return {0, 0}; }
    T op(T a, T b) const override { return {a.sum + b.sum, a.size + b.size}; }
  };

  struct F : public Monofunc<Affine<mint>, M> {
    T id() const override { return {1, 0}; }
    MT apply(T a, MT b) const override {
      return {a.a * b.sum + a.b * b.size, b.size};
    }
    T merge(T a, T b) const override { return a * b; }
  };

  LazySegmentTree<Node, Affine<mint>> seg(a, {0, 0}, {1, 0}, [](Node a, Node b){ return a + b; }, [](Affine<mint> a, Node b){ return Node{a.a * b.sum + a.b * b.size, b.size}; }, [](Affine<mint> a, Affine<mint> b){ return a * b; });

  rep(q, Q) {
    int type;
    cin >> type;
    if (type == 0) {
      int l, r, b, c;
      cin >> l >> r >> b >> c;
      seg.set(l, r, {b, c});
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.query(l, r).sum << endl;
    }
  }
}
