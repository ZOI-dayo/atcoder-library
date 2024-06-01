#pragma once

#include "../common/alias.hpp"

template <typename T> struct RBST {
private:
  /// 乱数シード生成器
  random_device rd;
  /// 乱数生成器
  mt19937 mt;
  /// 単位元
  T e;
  /// 演算
  function<T(T, T)> F;

public:
  /// ノード
  struct node_t {
    /// ノードの値
    T val;
    /// 部分木の大きさ
    size_t size;
    /// 部分木の総積
    T sum;
    /// 左右の子
    node_t *lch, *rch;
    /// 値のみによるノードの生成
    node_t(T val) : val(val), size(1), sum(val), lch(nullptr), rch(nullptr) {}
    /// 値と子によるノードの生成
    node_t(T val, node_t *lch, node_t *rch)
        : val(val), size(1), sum(val), lch(lch), rch(rch) {}
  };
  /// ノードの値を取得
  inline T val(const node_t *const t) const { return t ? t->val : e; }
  inline size_t size(const node_t *const t) const { return t ? t->size : 0; }
  inline T sum(const node_t *const t) const { return t ? t->sum : e; }
  inline node_t *update(node_t *const t) const {
    t->size = size(t->lch) + size(t->rch) + 1;
    t->sum = F(F(sum(t->lch), val(t)), sum(t->rch));
    return t;
  }

  RBST(T e, function<T(T, T)> F) : mt(rd()), e(e), F(F) {}

  node_t *root = nullptr;
  inline node_t *merge(node_t *const l, node_t *const r) {
    if (!l || !r)
      return l ? l : r;
    if (mt() % (l->size + r->size) < l->size) {
      l->rch = merge(l->rch, r);
      return update(l);
    } else {
      r->lch = merge(l, r->lch);
      return update(r);
    }
  }
  inline pair<node_t *, node_t *> split(node_t *const t, const size_t k) {
    if (!t)
      return {nullptr, nullptr};
    if (k <= size(t->lch)) {
      auto p = split(t->lch, k);
      t->lch = p.second;
      return {p.first, update(t)};
    } else {
      auto p = split(t->rch, k - size(t->lch) - 1);
      t->rch = p.first;
      return {update(t), p.second};
    }
  }
  inline node_t *insert_at(node_t *t, const size_t k, T val) {
    auto [l, r] = split(t, k);
    return t = merge(merge(l, new node_t(val)), r);
  }
  inline void insert_at(const size_t k, T val) {
    if (!root)
      root = new node_t(val);
    else
      root = insert_at(root, k, val);
  }
  inline node_t *erase_at(node_t *t, const size_t k) {
    auto [l, r] = split(t, k);
    auto [ll, lr] = split(r, 1);
    return t = merge(l, lr);
  }
  inline void erase_at(const size_t k) {
    assert(root);
    assert(0 <= k);
    assert(k < root->size);
    if (root->size == 1) {
      delete root;
      root = nullptr;
      return;
    }
    root = erase_at(root, k);
  }
  inline T get_at(const node_t *const t, const size_t k) const {
    assert(t);
    assert(0 <= k);
    assert(k < t->size);
    if (k < size(t->lch))
      return get_at(t->lch, k);
    if (k == size(t->lch))
      return t->val;
    return get_at(t->rch, k - size(t->lch) - 1);
  }

  inline T get_at(const size_t k) const { return get_at(root, k); }
  inline T query(node_t *&t, const size_t l, const size_t r) {
    auto [left, mid_right] = split(t, l);
    auto [mid, right] = split(mid_right, r - l);
    T res = sum(mid);
    t = merge(merge(left, mid), right);
    return res;
  }
  inline T query(const size_t l, const size_t r) { return query(root, l, r); }
  inline size_t size() const { return size(root); }
};

template <typename T> ostream &operator<<(ostream &os, const RBST<T> &t) {
  using node_t = typename RBST<T>::node_t;
  auto dump = [&os](auto fn, node_t *t) {
    if (!t)
      return;
    fn(fn, t->lch);
    os << t->val << " ";
    fn(fn, t->rch);
  };
  os << "RBST[ ";
  dump(dump, t.root);
  os << "]";
  return os;
}
