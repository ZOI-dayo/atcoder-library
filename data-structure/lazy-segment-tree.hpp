#pragma once

#include "util/all.hpp"

template <typename T, typename F>
class LazySegmentTree {
  size_t n;
  size_t height;
  function<T(T, T)> op;
  function<F(F, F)> merge;
  function<T(F, T, size_t)> apply;
  T e;
  F id;
  vec<T> data;
  vec<F> lazy;

  T eval(size_t i) {
    if (lazy[i] == id) return data[i];
    data[i] = apply(lazy[i], data[i], 1<<(height - bit_width(i)));
    if (i < n) {
      lazy[2 * i] = merge(lazy[2 * i], lazy[i]);
      lazy[2 * i + 1] = merge(lazy[2 * i + 1], lazy[i]);
    }
    lazy[i] = id;
    return data[i];
  }

public:
  LazySegmentTree(size_t n, const function<T(T,T)> &op, const function<F(F,F)> &merge, const function<T(F,T,size_t)> &apply, const T &e, const F &id)
    : n(bit_ceil(n)), height(bit_width(this->n)),
    op(op), merge(merge), apply(apply),
    e(e), id(id)
  {
    data.assign(2 * this->n, e);
    lazy.assign(2 * this->n, id);
  }

  LazySegmentTree(const vec<T> &v, const function<T(T,T)> &op, const function<F(F,F)> &merge, const function<T(F,T,size_t)> &apply, const T &e, const F &id)
    : LazySegmentTree(v.size(), op, merge, apply, e, id)
  {
    memcpy(&data[n], v.data(), v.size() * sizeof(T));
    for (int i = n - 1; i > 0; --i)
      data[i] = op(data[2 * i], data[2 * i + 1]);
  }

  void set(size_t l, size_t r, F f) {
    l += n;
    r += n;
    size_t l0 = l, r0 = r;
    for(size_t i=height; i>0; --i) {
      eval(l >> i);
      eval((r-1) >> i);
    }
    for (; l < r; l /= 2, r /= 2) {
      if (l % 2 == 1) {
        lazy[l] = merge(lazy[l], f);
        ++l;
      }
      if (r % 2 == 1) {
        --r;
        lazy[r] = merge(lazy[r], f);
      }
    }
    l = l0;
    r = r0 - 1;
    while(l > 1) {
      l /= 2;
      r /= 2;
      data[l] = op(eval(2 * l), eval(2 * l + 1));
      data[r] = op(eval(2 * r), eval(2 * r + 1));
    }
  }

  T query(size_t l, size_t r) {
    l += n;
    r += n;
    for(size_t i=height; i>0; --i) {
      eval(l >> i);
      eval((r-1) >> i);
    }
    T res_l = e, res_r = e;
    for (; l < r; l /= 2, r /= 2) {
      if (l % 2 == 1) {
        res_l = op(res_l, eval(l++));
      }
      if (r % 2 == 1) {
        res_r = op(eval(--r), res_r);
      }
    }
    return op(res_l, res_r);
  }

  T get(size_t i) {
    return query(i, i + 1);
  }

  T operator[](size_t i) {
    return get(i);
  }

  T operator[](size_t l, size_t r) {
    return query(l, r);
  }

};
