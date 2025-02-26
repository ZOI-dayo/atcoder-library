#pragma once

#include "util/all.hpp"

template <typename T>
class SegmentTree {
private:
  const int n;
  const T e;
  const function<T(T, T)> op;
  vector<T> data;

public:
  SegmentTree(const size_t n, const function<T(T,T)> &op, const T &e) : n(bit_ceil(n)), op(op), e(e) {
    data.assign(2 * this->n, e);
  }

  SegmentTree(const vec<T> &v, const function<T(T,T)> &op, const T &e) : SegmentTree(v.size(), op, e) {
    memcpy(&data[n], v.data(), v.size() * sizeof(T));
    for (int i = n - 1; i > 0; --i)
      data[i] = op(data[2 * i], data[2 * i + 1]);
  }

  T get(const size_t i) const {
    return data[i + n];
  }

  void set(size_t i, const T &x) {
    i += n;
    data[i] = x;
    for (i /= 2; i > 0; i /= 2) {
      data[i] = op(data[2 * i], data[2 * i + 1]);
    }
    return;
  }

  T query(size_t l, size_t r) const {
    T res_l = e, res_r = e;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l % 2 == 1) {
        res_l = op(res_l, data[l++]);
      }
      if (r % 2 == 1) {
        res_r = op(data[--r], res_r);
      }
    }
    return op(res_l, res_r);
  }

  T operator[](const size_t i) const {
    return get(i);
  }

  T operator[](const size_t l, const size_t r) const {
    return query(l, r);
  }

  // f(op([0...i])) == false となる最小の i を返す
  // f(op(a, b)) == f(a) && f(b) となるように設計してください
  size_t bin_search(const function<bool(T)> &f) const {
    auto find = [&](auto&& find, size_t i, size_t l, size_t r, T offset) -> size_t {
      if (f(op(offset, data[i]))) return r;
      if (l + 1 == r) return l + f(op(offset, data[i]));
      size_t m = midpoint(l, r);
      size_t res = find(find, 2 * i, l, m, offset);
      if (res != m) return res;
      return find(find, 2 * i + 1, m, r, op(offset, data[2*i]));
    };
    return find(find, 1, 0, n, e);
  }
};

template <typename T>
class SumSegmentTree : public SegmentTree<T> {
public:
  SumSegmentTree(const size_t n) : SegmentTree<T>(n, plus<T>(), 0) {}
  SumSegmentTree(const vec<T> &v) : SegmentTree<T>(v, plus<T>(), 0) {}
};

template <typename T>
class MinSegmentTree : public SegmentTree<T> {
public:
  MinSegmentTree(const size_t n) : SegmentTree<T>(n, [](T a,T b) { return min(a, b); }, numeric_limits<T>::max()) {}
  MinSegmentTree(const vec<T> &v) : SegmentTree<T>(v, [](T a, T b) { return min(a, b); }, numeric_limits<T>::max()) {}
};

template <typename T>
class MaxSegmentTree : public SegmentTree<T> {
public:
  MaxSegmentTree(const size_t n) : SegmentTree<T>(n, [](T a, T b) { return max(a, b); }, numeric_limits<T>::min()) {}
  MaxSegmentTree(const vec<T> &v) : SegmentTree<T>(v, [](T a, T b) { return max(a, b); }, numeric_limits<T>::min()) {}
};

