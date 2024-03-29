#pragma once

#include "../common/template.hpp"
#include "./monoid/monoid.hpp"

// 参考: https://qiita.com/ningenMe/items/bf66de877e3b97d35862

template <MonoidConcept M> struct SegmentTree {
  using T = typename M::T;

private:
  M _monoid;
  T e;

  // 要素数
  int _n;
  // SegTreeのノード上のデータ
  vec<T> _data;

public:
  explicit SegmentTree(int n) : _n(1), _monoid(M()), e(_monoid.e()) {
    while (_n < n)
      _n *= 2;
    _data = vec<T>(2 * _n, e);
  }
  explicit SegmentTree(const vec<T> &v) : _n(1), _monoid(M()), e(_monoid.e()) {
    while (_n < v.size())
      _n *= 2;
    _data = vec<T>(2 * _n, e);
    rep(i, v.size()) _data[i + _n] = v[i];
    for (int i = _n - 1; i > 0; --i)
      _data[i] = _monoid.op(_data[i << 1], _data[i << 1 | 1]);
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
      _data[i] = _monoid.op(_data[i << 1], _data[i << 1 | 1]);
  }
  T get(int i) const { return _data[i + _n]; }
  T query(int l, int r) {
    T l_val = e, r_val = e;
    // l, r(index)に+_nすると、最下段のseg-indexになる
    // l < r == l,rをすべて含む区間にはたどり着いていない
    // l/r >>= 1 : l/rを親に移動させる
    for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
      // lが左の子ならば、l<=iの結果はlの親の結果であるので、計算しない
      // lが右の子ならば、計算する必要がある
      if (l & 1)
        l_val = _monoid.op(l_val, _data[l++]);
      // l++をしても、l>>1が変わることはない
      // ただし、r=l+1のとき、答えはここのlである
      // ので、l<rに引っかかるようにして終了させている?

      // rが左の子ならば、rの親はギリギリ使われない、すなわちrの条件を満たす
      // rが右の子ならば、r-1は範囲に含まれるので、計算する必要がある
      if (r & 1)
        r_val = _monoid.op(_data[--r], r_val);
    }
    return _monoid.op(l_val, r_val);
  }
};
