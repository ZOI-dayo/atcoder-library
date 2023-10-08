#pragma once

#include "../common/template.hpp"

#if __cplusplus >= 202002L
template <class M>
concept Monoid = requires(M &x, M::T a, M::T b) {
  typename M::T;
  { M::e() } -> std::same_as<typename M::T>;
  { M::op(a, b) } -> std::same_as<typename M::T>;
};

#endif

// 参考: https://qiita.com/ningenMe/items/bf66de877e3b97d35862

#if __cplusplus >= 202002L
template <Monoid M>
#else
template <class M>
#endif
struct SegmentTree {
  using T = typename M::T;

private:
  // 単位元 デフォルトでは、min(a, e) = min(e, a) = a
  // T e;
  // 演算
  // function<T(T, T)> op;
  // 要素数
  int _n;
  // SegTreeのデータ
  vec<T> _data;
  // [l, r)の区間に対するクエリを処理する
  // kはSegTree上のindex
  T _query(int l, int r, int k) {
    // ↓再帰を使う場合
    /*
    if (r <= a || b <= l)
      return e;
    if (l <= a && b <= r)
      return _data[k];
    T l_val = _query(l, r, k<<1, a, (a + b)>>1);
    T r_val = _query(l, r, k<<1|1, (a + b)>>1, b);
    return op(l_val, r_val);
    */
    T l_val = M::e(), r_val = M::e();
    // l, r(index)に+_nすると、最下段のseg-indexになる
    // l < r == l,rをすべて含む区間にはたどり着いていない
    // l/r >>= 1 : l/rを親に移動させる
    for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
      // lが左の子ならば、l<=iの結果はlの親の結果であるので、計算しない
      // lが右の子ならば、計算する必要がある
      if (l & 1)
        l_val = M::op(l_val, _data[l++]);
      // l++をしても、l>>1が変わることはない
      // ただし、r=l+1のとき、答えはここのlである
      // ので、l<rに引っかかるようにして終了させている?

      // rが左の子ならば、rの親はギリギリ使われない、すなわちrの条件を満たす
      // rが右の子ならば、r-1は範囲に含まれるので、計算する必要がある
      if (r & 1)
        r_val = M::op(_data[--r], r_val);
    }
    return M::op(l_val, r_val);
  }

public:
  explicit SegmentTree(int n): _n(1) {
    while (_n < n)
      _n *= 2;
    _data = vec<T>(2 * _n, M::e());
  }

  void set(int i, T a) {
    // 1段目は1, 2段目は2~3, ... , 最下段はn~(2n-1)
    // より、iの最下段はi+n
    i += _n;
    _data[i] = a;
    // i >>= 1で、iを親のindexに変更
    // また、i==0となってしまうなら、i==1(頂点)であるので、終了
    // i<<1は、(更新後の)iの左の子
    // i<<1|1は、(更新後の)iの右の子 (+1を|1で表現)
    while (i >>= 1)
      _data[i] = M::op(_data[i << 1], _data[i << 1 | 1]);
  }
  T get(int i) const { return _data[i + _n]; }
  T query(int l, int r) const { return _query(l, r, 1); }
};

#if __cplusplus >= 202002L
template <Monoid M>
#else
template <class M>
#endif
using Segtree = SegmentTree<M>;

struct RMQMonoid {
  using T = int;
  static T e() { return numeric_limits<T>::max(); }
  static T op(T a, T b) { return min(a, b); }
};

Segtree<RMQMonoid> RMQSeg(int n) { return Segtree<RMQMonoid>(n); }
