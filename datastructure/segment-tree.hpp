#pragma once

#include "../common/template.hpp"
#include "./monoid/monoid.hpp"

// 参考: https://qiita.com/ningenMe/items/bf66de877e3b97d35862

template <typename T> struct SegmentTree {

private:
  /// 単位元
  T e;
  /// 演算
  function<T(T, T)> op;

  /// 要素数
  int n;
  /// SegTreeのノード上のデータ
  vec<T> data;

/// 左の子のインデックスを返す
#define L(i) (i << 1)
/// 右の子のインデックスを返す
#define R(i) (i << 1 | 1)
/// 親のインデックスを返す
#define P(i) (i >> 1)

public:
  /**
   * @brief 個数から空のSegmentTreeを生成する
   *
   * @param length 要素数
   * @param e 単位元
   * @param op 演算
   */
  explicit SegmentTree(int length, T e, function<T(T, T)> op)
      : e(e), op(op), n(bit_ceil(length)), data(2 * n, e) {}

  /**
   * @brief 既存のベクトルからSegmentTreeを生成する
   *
   * @param v データ
   * @param e 単位元
   * @param op 演算
   */
  explicit SegmentTree(const vec<T> &v, T e, function<T(T, T)> op)
      : e(e), op(op), n(bit_ceil(v.size())), data(2 * n, e) {
    rep(i, v.size()) data[i + n] = v[i];
    for (int i = n - 1; i > 0; --i)
      data[i] = op(data[L(i)], data[R(i)]);
  }

  /**
   * @brief i番目の要素を取得する
   *
   * @param i インデックス (0-indexed)
   * @param a 更新後の要素
   */
  void set(int i, T a) {
    i += n;
    data[i] = a;
    while (i = P(i), i > 0)
      data[i] = op(data[L(i)], data[R(i)]);
  }

  /**
   * @brief i番目の要素を取得する
   *
   * @param i インデックス (0-indexed)
   * @return i番目の要素
   */
  T get(int i) const { return data[i + n]; }

  /**
   * @brief [l, r)の範囲に対するクエリを行う
   *
   * @param l クエリの左端
   * @param r クエリの右端
   * @return クエリの結果
   */
  T query(int l, int r) {
    T l_val = e, r_val = e;
    l += n, r += n;
    while (l < r) {
      if (l & 1)
        l_val = op(l_val, data[l++]);
      if (r & 1)
        r_val = op(data[--r], r_val);
      l = P(l), r = P(r);
    }
    return op(l_val, r_val);
  }
};
