#pragma once

#include <bit>
#include <cstdint>
#include <functional>

namespace zoi {
namespace datastructure {

// 参考 https://qiita.com/ningenMe/items/bf66de877e3b97d35862

/**
 * @brief 遅延セグメント木
 *
 * @tparam T ノードの型
 * @tparam F 操作情報の型
 */
template <typename T, typename F> struct LazySegmentTree {
private:
  /// データの単位元
  const T e;
  /// 操作の単位元
  const F id;

  /// データの演算(ノードのマージ)
  const std::function<T(T, T)> op;
  /// ノードの更新 (操作の適用)
  const std::function<T(F, T)> apply;
  /// 操作のマージ
  const std::function<F(F, F)> merge;

  // 要素数
  uint32_t _n;
  uint32_t _height;

  /// セグ木のノード情報
  std::vector<T> _data;
  /// セグ木の遅延情報
  std::vector<F> _lazy;

  /// 左の子のインデックスを返す
#define L(i) (i << 1)
  /// 右の子のインデックスを返す
#define R(i) (i << 1 | 1)
  /// 親のインデックスを返す
#define P(i) (i >> 1)

  /**
   * @brief k番目のノードの遅延情報を解消し、子ノードに伝搬する O(log N) * merge
   *
   * @param k ノード番号 (1-indexed, seg-index)
   */
  inline void eval(int32_t k) {
    if (_lazy[k] == id)
      return;
    _data[k] = apply(_lazy[k], _data[k]);
    if (k < _n) {
      _lazy[L(k)] = merge(_lazy[L(k)], _lazy[k]);
      _lazy[R(k)] = merge(_lazy[R(k)], _lazy[k]);
    }
    _lazy[k] = id;
  }

public:
  // n: 要素数, e: 単位元, id: 操作情報の単位元, op: 演算, update:
  // ノードの更新(fn,val->val), merge:
  // 操作aがすでに行われている状態に操作bを適用したときの操作
  // TODO: 2つの実装が別れているのをどうにかする

  /**
   * @brief 要素数から空のLazySegmentTreeを生成する O(length)
   *
   * @param length 要素数
   * @param e 単位元
   * @param id 操作情報の単位元
   * @param op ノードのマージ
   * @param apply 操作の適用
   * @param merge 操作のマージ
   */
  explicit inline LazySegmentTree(const uint32_t length, const T e, const F id,
                                  const std::function<T(T, T)> op,
                                  const std::function<T(F, T)> apply,
                                  const std::function<F(F, F)> merge)
      : e(e), id(id), op(op), apply(apply), merge(merge),
        _n(std::bit_ceil(length)), _height(std::bit_width(_n) - 1),
        _data(2 * _n, e), _lazy(2 * _n, id) {}

  /**
   * @brief 既存のベクトルからLazySegmentTreeを生成する O(length) * op
   *
   * @param data データ
   * @param e 単位元
   * @param id 操作情報の単位元
   * @param op ノードのマージ
   * @param apply 操作の適用
   * @param merge 操作のマージ
   */
  explicit inline LazySegmentTree(std::vector<T> &data, const T e, const F id,
                                  const std::function<T(T, T)> op,
                                  const std::function<T(F, T)> apply,
                                  const std::function<F(F, F)> merge)
      : e(e), id(id), op(op), apply(apply), merge(merge),
        _n(bit_ceil(data.size())), _height(std::bit_width(_n) - 1),
        _data(2 * _n, e), _lazy(2 * _n, id) {
    for (int i = 0; i < data.size(); ++i)
      _data[i + _n] = data[i];
    for (int i = _n - 1; i > 0; --i)
      _data[i] = op(_data[L(i)], _data[R(i)]);
  }

  /**
   * @brief [l, r)の区間に対して操作fを適用する O(log N) * op
   *
   * @param l 左端 (0-indexed)
   * @param r 右端 (0-indexed)
   * @param f 操作
   */
  inline void set(int32_t l, int32_t r, F f) {
    // a, bはseg-index [a,b]
    int32_t a = l + _n, b = r + _n - 1;

    // 上から下へとlazyを伝搬させる
    for (int32_t i = _height; 0 < i; --i)
      eval(a >> i), eval(b >> i);
    // bを [a, b]から[a, b)にする
    for (b++; a < b; a >>= 1, b >>= 1) {
      if (a & 1)
        _lazy[a] = merge(_lazy[a], f), eval(a), a++;
      if (b & 1)
        --b, _lazy[b] = merge(_lazy[b], f), eval(b);
    }
    // a, bをseg-index [a,b]に戻す
    a = l + _n, b = r + _n - 1;
    // a,bを親に移しつつ、aが実在頂点の間
    while ((a >>= 1), (b >>= 1), a) {
      if (_lazy[a] == id) {
        _data[a] = op(apply(_lazy[(a << 1) | 0], _data[(a << 1) | 0]),
                      apply(_lazy[(a << 1) | 1], _data[(a << 1) | 1]));
      }
      if (_lazy[b] == id) {
        _data[b] = op(apply(_lazy[(b << 1) | 0], _data[(b << 1) | 0]),
                      apply(_lazy[(b << 1) | 1], _data[(b << 1) | 1]));
      }
    }
  }

  /**
   * @brief [l, r)の区間に対するクエリを処理する
   *
   * @param l 左端 (0-indexed)
   * @param r 右端 (0-indexed)
   * @return T クエリの結果
   */
  inline T query(int32_t l, int32_t r) {
    // a, bはseg-index [a,b]
    int32_t a = l + _n, b = r + _n - 1;
    // 上から下へとlazyを伝搬させる
    for (int32_t i = _height; 0 <= i; --i)
      eval(a >> i), eval(b >> i);
    T vl = e, vr = e;
    // bを [a, b]から[a, b)にする
    for (b++; a < b; a >>= 1, b >>= 1) {
      if (a & 1)
        vl = op(vl, apply(_lazy[a], _data[a])), a++;
      if (b & 1)
        b--, vr = op(apply(_lazy[b], _data[b]), vr);
    }
    return op(vl, vr);
  }

  /**
   * @brief i番目の要素を取得する
   *
   * @param i インデックス (0-indexed)
   * @return T i番目の要素
   */
  inline T get(int32_t i) { return query(i, i + 1); }

#undef L
#undef R
#undef P
};

} // namespace datastructure
} // namespace zoi
