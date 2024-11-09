#pragma once

#include "util/all.hpp"
// #include "segment-tree/monoid.hpp"

template <typename M, typename N>
class DynamicSegmentTreeNode {
private:
  using T = typename M::value_type;
  using Node = DynamicSegmentTreeNode<M, N>;

  T val;
  Node *p, *lc, *rc;
  const N l, r;
public:

  DynamicSegmentTreeNode(T val, N range_l, N range_r)
    : val(val),
    p(nullptr), lc(nullptr), rc(nullptr),
    l(range_l), r(range_r) {}
  DynamicSegmentTreeNode(T val, Node *p, bool child_index)
    : val(val),
    p(p), lc(nullptr), rc(nullptr),
    l(child_index ? p->l : p->mid()),
    r(!child_index ? p->r : p->mid()) {}

  T mid() const {
    return l + (r - l) / 2;
  }

  Node *child(bool index) const {
    Node* res = index ? lc : rc;
    if (res == nullptr) {
      res = new Node(M::e, this, index);
      index ? lc = res : rc = res;
    }
    return res;
  }

  Node *make_parent() {
    assert(p == nullptr);
    assert(l == 0);
    Node *res = new Node(val, 0, r * 2);
    res->lc = this;
    p = res;
    return p;
  }
};

template <typename M, typename N>
class DynamicSegmentTree {
private:
  using T = typename M::value_type;
  using Node = DynamicSegmentTreeNode<M, N>;
  Node *root;

  Node *get_node(int i) const {
    Node *node = root;
    while (root->r <= i) {
      root = root->make_parent();
    }
    while (node->l + 1 < node->r) {
      node = node->child(node->mid() <= i);
    }
    return node;
  }

  T _query(Node *node, N l, N r) {
    if (node->r <= l || r <= node->l) {
      return M::e;
    }
    if (l <= node->l && node->r <= r) {
      return node->val;
    }
    return M::op(_query(node->lc, l, r), _query(node->rc, l, r));
  }

public:
  DynamicSegmentTree() : root(new Node(M::e, nullptr, 0, 1)) {}

  void set(N i, T x) {
    Node *node = get_node(i);
    node->val = x;
    while (node->p != nullptr) {
      node = node->p;
      node->val = M::op(node->lc->val, node->rc->val);
    }
  }

  T get(N i) {
    return get_node(i)->val;
  }

  T operator[](N i) {
    return get(i);
  }

  T query(N l, N r) {
    return _query(root, l, r);
  }

};
