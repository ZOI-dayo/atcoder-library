#pragma once

#include "../common/template.hpp"
#include "./monoid/monofunc.hpp"

// 参考 https://qiita.com/ningenMe/items/bf66de877e3b97d35862

// T : Nodeの型, F : 操作情報
template <MonofuncConcept F> struct LazySegmentTree {
private:
  using M = typename F::M;
  using FT = typename F::T;
  using MT = typename M::T;
  // 単位元 デフォルトでは、min(a, e) = min(e, a) = a
  const MT e;
  const FT id;
  // Monoids
  const M _monoid;
  const F _monofunc;
  // 演算
  // const function<T(T, T)> op;
  // const function<T(F, T)> update;
  // const function<F(F, F)> merge;
  // 要素数
  int32_t _n;
  int32_t _height;
  // SefTreeのデータ
  vec<MT> _data;
  vec<FT> _lazy;

  // 自分の遅延を解消して子に伝搬する
  inline void eval(int32_t k) {
    if (_lazy[k] == id)
      return;
    _data[k] = _monofunc.apply(_lazy[k], _data[k]);
    if (k < _n) {
      _lazy[k << 1 | 0] = _monofunc.merge(_lazy[k << 1 | 0], _lazy[k]);
      _lazy[k << 1 | 1] = _monofunc.merge(_lazy[k << 1 | 1], _lazy[k]);
    }
    _lazy[k] = id;
  }

public:
  // n: 要素数, e: 単位元, id: 操作情報の単位元, op: 演算, update:
  // ノードの更新(fn,val->val), merge:
  // 操作aがすでに行われている状態に操作bを適用したときの操作
  // TODO: 2つの実装が別れているのをどうにかする
  explicit inline LazySegmentTree(const int32_t n)
      : _monoid(M()), _monofunc(F()), e(_monoid.e()), id(_monofunc.id()) {
    _n = 1;
    _height = 1;
    while (_n < n)
      _n <<= 1, _height++;
    _data = vec<MT>(_n << 1, e);
    _lazy = vec<FT>(_n << 1, id);
  }
  explicit inline LazySegmentTree(vec<MT> &data)
      : _monoid(M()), _monofunc(F()), e(_monoid.e()), id(_monofunc.id()) {
    _n = 1;
    _height = 1;
    while (_n < data.size())
      _n <<= 1, _height++;
    _data = vec<MT>(_n << 1, e);
    _lazy = vec<FT>(_n << 1, id);
    rep(i, data.size()) _data[i + _n] = data[i];
    for (int i = _n - 1; i > 0; --i)
      _data[i] = _monoid.op(_data[i << 1], _data[i << 1 | 1]);
  }
  /*
  inline LazySegmentTree(const T e, const F id,
                         const function<T(T, T)> op,
                         const function<T(F, T)> update,
                         const function<F(F, F)> merge,
                         vec<T> &v)
      : e(e), id(id), op(op), update(update), merge(merge) {
    _n = 1;
    _height = 1;
    while (_n < v.size())
      _n <<= 1, _height++;
    _data.resize(_n << 1, e);
    for(int i=0; i<v.size(); ++i) _data[i + _n] = v[i];
    _lazy = vec<F>(_n << 1, id);
  }
  */

  inline void set(int32_t l, int32_t r, FT f) {
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
    int32_t a = l + _n, b = r + _n - 1;

    // 上から下へとlazyを伝搬させる
    for (int32_t i = _height; 0 < i; --i)
      eval(a >> i), eval(b >> i);
    // bを [a, b]から[a, b)にする
    for (b++; a < b; a >>= 1, b >>= 1) {
      if (a & 1)
        _lazy[a] = _monofunc.merge(_lazy[a], f), eval(a), a++;
      if (b & 1)
        --b, _lazy[b] = _monofunc.merge(_lazy[b], f), eval(b);
    }
    // a, bをseg-index [a,b]に戻す
    a = l + _n, b = r + _n - 1;
    // a,bを親に移しつつ、aが実在頂点の間
    while ((a >>= 1), (b >>= 1), a) {
      if (_lazy[a] == id) {
        // _data[(a << 1) | 0] = update(_lazy[(a << 1) | 0], _data[(a << 1) |
        // 0]); _data[(a << 1) | 1] = update(_lazy[(a << 1) | 1], _data[(a << 1)
        // | 1]); _data[a] = op(_data[(a << 1) | 0], _data[(a << 1) | 1]);
        _data[a] = _monoid.op(
            _monofunc.apply(_lazy[(a << 1) | 0], _data[(a << 1) | 0]),
            _monofunc.apply(_lazy[(a << 1) | 1], _data[(a << 1) | 1]));
      }
      if (_lazy[b] == id) {
        // _data[(b << 1) | 0] = update(_lazy[(b << 1) | 0], _data[(b << 1) |
        // 0]); _data[(b << 1) | 1] = update(_lazy[(b << 1) | 1], _data[(b << 1)
        // | 1]); _data[b] = op(_data[(b << 1) | 0], _data[(b << 1) | 1]);
        _data[b] = _monoid.op(
            _monofunc.apply(_lazy[(b << 1) | 0], _data[(b << 1) | 0]),
            _monofunc.apply(_lazy[(b << 1) | 1], _data[(b << 1) | 1]));
      }
    }
  }

  // [l, r)の区間に対するクエリを処理する
  // kはSegTree上のindex
  inline MT query(int32_t l, int32_t r) {
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
    int32_t a = l + _n, b = r + _n - 1;
    // 上から下へとlazyを伝搬させる
    for (int32_t i = _height; 0 <= i; --i)
      eval(a >> i), eval(b >> i);
    // line_debug();
    // printd(_data);
    // printd(_lazy);
    MT vl = e, vr = e;
    // bを [a, b]から[a, b)にする
    for (b++; a < b; a >>= 1, b >>= 1) {
      if (a & 1)
        vl = _monoid.op(vl, _monofunc.apply(_lazy[a], _data[a])), a++;
      if (b & 1)
        b--, vr = _monoid.op(_monofunc.apply(_lazy[b], _data[b]), vr);
    }
    return _monoid.op(vl, vr);
  }
  inline MT get(int32_t i) { return query(i, i + 1); }
};
/*
template <typename T, typename F> using LazySegtree = LazySegmentTree<T, F>;

template <typename T, typename F> inline LazySegtree<T, F> RMQLazySeg(int n) {
  return LazySegmentTree<T, F>(
      n, numeric_limits<T>::max(), 0, [](T a, T b) { return min(a, b); },
      [](F a, T b) { return b + a; }, [](F a, F b) { return b + a; });
}
*/
