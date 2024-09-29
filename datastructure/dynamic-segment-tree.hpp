#pragma once

#include <bit>
#include <functional>

namespace zoi {
namespace datastructure {

/**
 * @brief セグメント木
 *
 * @tparam T ノードの型
 */
template <typename T> struct DynamicSegmentTree {

private:
  /// 単位元
  T e;
  /// 演算
  std::function<T(T, T)> op;

  /// 要素数
  int n;

  /// ノードの構造体
  struct Node {

    /// ノードの値
    T val;

    /// 初期化用の値
    T e;

    /// 親ノード, 左の子ノード, 右の子ノード
    Node *p, *l_child, *r_child;

    /// ノードの範囲
    int l, r;

    Node(T val, T e, int l, int r)
        : val(val), e(e), p(nullptr), l_child(nullptr), r_child(nullptr), l(l),
          r(r) {}

    Node(T val, Node *p, bool child_index)
        : val(val), e(p->e), p(p), l_child(nullptr), r_child(nullptr),
          l(!child_index ? p->l : p->mid()), r(!child_index ? p->mid() : p->r) {
    }

    /// ノードの範囲の中央
    int mid() const { return (l + r) / 2; }

    /// 子ノードを取得する
    Node *child(bool child_index) {
      if (child_index == 0) {
        if (l_child == nullptr)
          l_child = new Node(e, this, 0);
        return l_child;
      } else {
        if (r_child == nullptr)
          r_child = new Node(e, this, 1);
        return r_child;
      }
    }

    /// 子ノードの情報からvalを更新する
    void update(auto &op) {
      T l_val = l_child == nullptr ? e : l_child->val;
      T r_val = r_child == nullptr ? e : r_child->val;
      val = op(l_val, r_val);
    }
  };

  Node *root;

public:
  /**
   * @brief 個数から空のSegmentTreeを生成する O(1)
   *
   * @param length 要素数
   * @param e 単位元
   * @param op 演算
   */
  inline explicit DynamicSegmentTree(int length, T e, std::function<T(T, T)> op)
      : e(e), op(op), n(std::bit_ceil((unsigned)length)),
        root(new Node(e, e, 0, n)) {}

  /**
   * @brief i番目の要素を取得する O(log n)
   */
  inline Node *get_node(int i) const {
    Node *node = root;
    while (node->l + 1 < node->r) {
      node = node->child(node->mid() <= i);
    }
    return node;
  }

  /**
   * @brief i番目の要素を変更する O(log n) * op
   *
   * @param i インデックス (0-indexed)
   * @param a 更新後の要素
   */
  inline void set(int i, T a) {
    Node *node = get_node(i);
    node->val = a;
    while (node->p != nullptr) {
      node = node->p;
      node->update(op);
    }
  }

  /**
   * @brief i番目の要素を取得する O(log n)
   *
   * @param i インデックス (0-indexed)
   * @return i番目の要素
   */
  inline T get(int i) const { return get_node(i)->val; }

  /**
   * @brief [l, r)の範囲に対するクエリを行う O(log n) * op
   *
   * @param l クエリの左端 (0-indexed)
   * @param r クエリの右端 (0-indexed)
   * @return クエリの結果
   */
  inline T query(int l, int r) const { return _query(root, l, r); }

private:
  /**
   * @brief 特定のノードに対し、[l, r)の範囲に対するクエリを行う O(log n) * op
   *
   * @param node クエリを行うノード
   * @param l クエリの左端 (0-indexed)
   * @param r クエリの右端 (0-indexed)
   * @return クエリの結果
   */
  inline T _query(Node *node, int l, int r) const {
    if (r <= node->l || node->r <= l)
      return e;
    if (l <= node->l && node->r <= r)
      return node->val;
    return op(_query(node->child(0), l, r), _query(node->child(1), l, r));
  }
};

} // namespace datastructure
} // namespace zoi
