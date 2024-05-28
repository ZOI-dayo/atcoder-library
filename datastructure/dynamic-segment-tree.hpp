#pragma once

#include "../common/alias.hpp"

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
  function<T(T, T)> op;

  /// 要素数
  int n;

  struct Node {
    T val;
    Node *p, *l_child, *r_child;
    int l, r;
    Node(T val, int l, int r) :
      val(val), p(nullptr), l_child(nullptr), r_child(nullptr),
      l(l), r(r) {}
    Node(T val, Node *p, bool is_l_child) :
      val(val), p(p), l_child(nullptr), r_child(nullptr),
      l(is_l_child ? p->l : p->mid()),
      r(is_l_child ? p->mid() : p->r) {}
    int size() const { return r - l; }
    int mid() const { return (l + r) / 2; }
    Node* child(bool is_l_child, T e) {
      if(is_l_child) {
        if(l_child == nullptr) l_child = new Node(e, this, true);
        return l_child;
      } else {
        if(r_child == nullptr) r_child = new Node(e, this, false);
        return r_child;
      }
    }
    bool is_l_area(int i) const { return i < mid(); }
    bool is_bottom() const { return l + 1 == r; }
    bool is_l_child() const { return p->l_child == this; }
  };

  Node* root;

public:
  /**
   * @brief 個数から空のSegmentTreeを生成する O(n)
   *
   * @param length 要素数
   * @param e 単位元
   * @param op 演算
   */
  inline explicit DynamicSegmentTree(int length, T e, function<T(T, T)> op)
      : e(e), op(op), n(bit_ceil(length)), root(new Node(e, 0, n)) {}

  inline Node* get_node(int i) const {
    Node *node = root;
    while(!node->is_bottom()) {
      node = node->child(node->is_l_area(i), e);
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
    while(node->p != nullptr) {
      node->p->val = op(node->p->child(1, e)->val, node->p->child(0,e)->val);
      node = node->p;
    }
  }

  /**
   * @brief i番目の要素を取得する O(1)
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
  inline T query(int l, int r) const {
    return _query(root, l, r);
  }
  inline T _query(Node *node, int l, int r) const {
    if(r <= node->l || node->r <= l) return e;
    if(l <= node->l && node->r <= r) return node->val;
    return op(_query(node->child(1, e), l, r), _query(node->child(0, e), l, r));
  }

};
