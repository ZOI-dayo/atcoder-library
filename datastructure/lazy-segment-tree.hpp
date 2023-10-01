#pragma once

#include "../common/template.hpp"

// 参考 https://qiita.com/ningenMe/items/bf66de877e3b97d35862

// T : Nodeの型, F : 操作情報
template <typename T, typename F> struct LazySegmentTree {
private:
  // 単位元 デフォルトでは、min(a, e) = min(e, a) = a
  const T e;
  const F id;
  // 演算
  const function<T(T, T)> op;
  const function<T(F, T)> update;
  const function<F(F, F)> merge;
  // 要素数
  int _n;
  int _height;
  // SefTreeのデータ
  vec<T> _data, _lazy;

public:
  // n: 要素数, e: 単位元, id: 操作情報の単位元, op: 演算, update:
  // ノードの更新(fn,val->val), merge:
  // 操作aを、操作bがすでに行われている状態に適用したときの操作
  LazySegmentTree(int n, T e, F id, function<T(T, T)> op,
                  function<T(F, T)> update, function<F(F, F)> merge)
      : e(e), id(id), op(op), update(update), merge(merge) {
    _n = 1;
    _height = 1;
    while (_n < n)
      _n <<= 1, _height++;
    _data = vec<T>(_n << 1, e);
    _lazy = vec<T>(_n << 1, id);
  }

  // 自分の遅延を解消して子に伝搬する
  inline void eval(int k) {
    if (_lazy[k] == id)
      return;
    _data[k] = update(_lazy[k], _data[k]);
    if (k < _n) {
      _lazy[k << 1 | 0] = merge(_lazy[k], _lazy[k << 1 | 0]);
      _lazy[k << 1 | 1] = merge(_lazy[k], _lazy[k << 1 | 1]);
    }
    _lazy[k] = id;
  }

  inline void set(int l, int r, F f) {
    /*
    eval(k);
    if (l <= a && b <= r) { // 完全に内側
      _lazy[k] = merge(f, _lazy[k]);
      eval(k);
    } else if (a < r && l < b) { // 一部区間が被る
      _set(l, r, f, (k << 1) + 1, a, (a + b) >> 1);
      _set(l, r, f, (k << 1) + 2, (a + b) >> 1, b);
      _data[k] = op(_data[(k << 1) + 1], _data[(k << 1) + 2]);
    }
    */
    // a, bはseg-index [a,b]
    int a = l + _n, b = r + _n - 1;

    // 上から下へとlazyを伝搬させる
    for (int i = _height; 0 < i; --i)
      eval(a >> i), eval(b >> i);
    // bを [a, b]から[a, b)にする
    for (b++; a < b; a >>= 1, b >>= 1) {
      if (a & 1)
        _lazy[a] = merge(f, _lazy[a]), eval(a), a++;
      if (b & 1)
        --b, _lazy[b] = merge(f, _lazy[b]), eval(b);
    }
    // a, bをseg-index [a,b]に戻す
    a = l + _n, b = r + _n - 1;
    // a,bを親に移しつつ、aが実在頂点の間
    while ((a >>= 1), (b >>= 1), a) {
      if (_lazy[a] == id) {
        _data[(a << 1) | 0] = update(_lazy[(a << 1) | 0], _data[(a << 1) | 0]);
        _data[(a << 1) | 1] = update(_lazy[(a << 1) | 1], _data[(a << 1) | 1]);
        _data[a] = op(_data[(a << 1) | 0], _data[(a << 1) | 1]);
      }
      if (_lazy[b] == id) {
        _data[(b << 1) | 0] = update(_lazy[(b << 1) | 0], _data[(b << 1) | 0]);
        _data[(b << 1) | 1] = update(_lazy[(b << 1) | 1], _data[(b << 1) | 1]);
        _data[b] = op(_data[(b << 1) | 0], _data[(b << 1) | 1]);
      }
    }
  }

  // [l, r)の区間に対するクエリを処理する
  // kはSegTree上のindex
  inline T query(int l, int r) {
    // ↓再帰
    /*
    eval(k);
    if (r <= a || b <= l)
      return e;
    if (l <= a && b <= r)
      return _data[k];
    T l_val = _query(l, r, (k << 1) + 1, a, (a + b) >> 1);
    T r_val = _query(l, r, (k << 1) + 2, (a + b) >> 1, b);
    return op(l_val, r_val);
    */

    // a, bはseg-index [a,b]
    int a = l + _n, b = r + _n - 1;
    // 上から下へとlazyを伝搬させる
    for (int i = _height; 0 <= i; --i)
      eval(a >> i), eval(b >> i);
    // line_debug();
    // printd(_data);
    // printd(_lazy);
    int vl = e, vr = e;
    // bを [a, b]から[a, b)にする
    for (b++; a < b; a >>= 1, b >>= 1) {
      if (a & 1)
        vl = op(vl, _data[a] = update(_lazy[a], _data[a])), a++;
      if (b & 1)
        b--, vr = op(_data[b] = update(_lazy[b], _data[b]), vr);
    }
    // line_debug();
    return op(vl, vr);
  }
};
template <typename T, typename F> using LazySegtree = LazySegmentTree<T, F>;

template <typename T, typename F> LazySegtree<T, F> RMQLazySeg(int n) {
  return LazySegmentTree<T, F>(
      n, numeric_limits<T>::max(), 0, [](T a, T b) { return min(a, b); },
      [](F a, T b) { return b + a; }, [](F a, F b) { return b + a; });
}
