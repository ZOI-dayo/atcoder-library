#pragma once

#include "../../common/template.hpp"

// Range Min Query
template <typename T>
struct SegmentTree {
 private:
  // 単位元 デフォルトでは、min(a, e) = min(e, a) = a
  T e;
  // 演算
  function<T(T, T)> op;
  // 要素数
  int _n;
  // SefTreeのデータ
  vec<T> _data;
  // [l, r)の区間に対するクエリを処理する
  // kはSegTree上のindex, [a, b)は節点kが担当する区間
  T _query(int l, int r, int k, int a, int b) {
    if(r <= a || b <= l) return e;
    if(l <= a && b <= r) return _data[k];
    T l_val = _query(l, r, k*2+1, a, (a+b)/2);
    T r_val = _query(l, r, k*2+2, (a+b)/2, b);
    return op(l_val, r_val);
  }

 public:
  explicit SegmentTree(int n) : SegmentTree(n, numeric_limits<T>::max(), min) {}

  SegmentTree(int n, T e, function<T(T, T)> op) : e(e), op(op) {
    _n = 1;
    while (_n < n) _n *= 2;
    data = vec<T>(2 * n, e);
  }

  void set(int i, T a) {
    // 1段目は0, 2段目は1~2, ... , 最下段は(n-1)~(2n-2)
    // より、iの最下段はi+n-1
    i += _n-1;
    _data[i] = a;
    while (i > 0) {
      i = (i-1)/2;
      _data[i] = op(_data[i*2+1], _data[i*2+2]);
    }
  }
  T get(int i) {
    return _data[i+_n-1];
  }
  T query(int l, int r) {
    return _query(l, r, 0, 0, _n);
  }
};
template <typename T>
using Segtree = SegmentTree<T>;
