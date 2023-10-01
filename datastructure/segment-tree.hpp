#pragma once

#include "../common/template.hpp"

// 参考: https://qiita.com/ningenMe/items/bf66de877e3b97d35862

template <typename T> struct SegmentTree {
private:
  // 単位元 デフォルトでは、min(a, e) = min(e, a) = a
  T e;
  // 演算
  function<T(T, T)> op;
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
    T l_val = e, r_val = e;
    // l, r(index)に+_nすると、最下段のseg-indexになる
    // l < r == l,rをすべて含む区間にはたどり着いていない
    // l/r >>= 1 : l/rを親に移動させる
    for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
      // lが左の子ならば、l<=iの結果はlの親の結果であるので、計算しない
      // lが右の子ならば、計算する必要がある
      if (l & 1)
        l_val = op(l_val, _data[l++]);
      // l++をしても、l>>1が変わることはない
      // ただし、r=l+1のとき、答えはここのlである
      // ので、l<rに引っかかるようにして終了させている?

      // rが左の子ならば、rの親はギリギリ使われない、すなわちrの条件を満たす
      // rが右の子ならば、r-1は範囲に含まれるので、計算する必要がある
      if (r & 1)
        r_val = op(_data[--r], r_val);
    }
    return op(l_val, r_val);
  }

public:
  SegmentTree(int n, T e, function<T(T, T)> op) : e(e), op(op) {
    _n = 1;
    while (_n < n)
      _n *= 2;
    _data = vec<T>(2 * _n, e);
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
      _data[i] = op(_data[i << 1], _data[i << 1 | 1]);
  }
  T get(int i) { return _data[i + _n]; }
  T query(int l, int r) { return _query(l, r, 1); }
};
template <typename T> using Segtree = SegmentTree<T>;

template <typename T> Segtree<T> RMQSeg(int n) {
  return SegmentTree<T>(n, numeric_limits<T>::max(),
                        [](T a, T b) { return min(a, b); });
}
