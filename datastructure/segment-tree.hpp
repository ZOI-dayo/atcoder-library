#pragma once

#include <cstdint>
#include <functional>

namespace zoi {
namespace datastructure {

// 参考: https://qiita.com/ningenMe/items/bf66de877e3b97d35862

/**
 * @brief セグメント木
 *
 * @tparam T ノードの型
 */
template <typename T> struct SegmentTree {

private:
  /// 単位元
  T e;
  /// 演算
  std::function<T(T, T)> op;

  /// 要素数
  int n;
  /// SegTreeのノード上のデータ
  std::vector<T> data;

  /// 左の子のインデックスを返す
#define L(i) (i << 1)
  /// 右の子のインデックスを返す
#define R(i) (i << 1 | 1)
  /// 親のインデックスを返す
#define P(i) (i >> 1)

public:
  /**
   * @brief 個数から空のSegmentTreeを生成する O(n)
   *
   * @param length 要素数
   * @param e 単位元
   * @param op 演算
   */
  inline explicit SegmentTree(uint32_t length, T e, std::function<T(T, T)> op)
      : e(e), op(op), n(std::bit_ceil(length)), data(2 * n, e) {}

  /**
   * @brief 既存のベクトルからSegmentTreeを生成する O(n) * op
   *
   * @param v データ
   * @param e 単位元
   * @param op 演算
   */
  inline explicit SegmentTree(const std::vector<T> &v, T e, std::function<T(T, T)> op)
      : e(e), op(op), n(bit_ceil(v.size())), data(2 * n, e) {
    for(int i=0; i<v.size(); ++i) data[i + n] = v[i];
    for (int i = n - 1; i > 0; --i)
      data[i] = op(data[L(i)], data[R(i)]);
  }

  /**
   * @brief i番目の要素を変更する O(log n) * op
   *
   * @param i インデックス (0-indexed)
   * @param a 更新後の要素
   */
  inline void set(int i, T a) {
    i += n;
    data[i] = a;
    while (i = P(i), i > 0)
      data[i] = op(data[L(i)], data[R(i)]);
  }

  /**
   * @brief i番目の要素を取得する O(1)
   *
   * @param i インデックス (0-indexed)
   * @return i番目の要素
   */
  inline T get(int i) const { return data[i + n]; }

  /**
   * @brief [l, r)の範囲に対するクエリを行う O(log n) * op
   *
   * @param l クエリの左端 (0-indexed)
   * @param r クエリの右端 (0-indexed)
   * @return クエリの結果
   */
  inline T query(int l, int r) const {
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

#undef L
#undef R
#undef P
};

} // namespace datastructure
} // namespace zoi
