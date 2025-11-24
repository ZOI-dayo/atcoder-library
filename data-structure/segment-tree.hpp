#pragma once

#include "../util/all.hpp"

template <class T, const T e, const auto op>
class SegmentTree {
private:
  const int n;
  vec<T> data;

public:

  class pointer {
  private:
    SegmentTree<T, e, op> &parent;
    const int i;
  public:
    pointer(SegmentTree<T, e, op> &seg, int i): parent(seg), i(i + seg.n) {}
    inline operator T() const {
      return parent.data[i];
    }
    inline pointer& operator=(const T &other) {
      auto idx = i;
      parent.data[idx] = other;
      while(idx) {
        idx >>= 1;
        parent.data[idx] = op(parent.data[idx << 1], parent.data[(idx << 1) | 1]);
      }
      return *this;
    }
  };

  inline explicit SegmentTree(const int n) : n(bit_ceil(n)) {
    data.resize(2 * this->n, e);
  }

  inline explicit SegmentTree(const vec<T> &v) : SegmentTree(v.size()) {
    memcpy(&data[n], v.data(), v.size() * sizeof(T));
    rrep(i, 0, n) data[i] = op(data[i<<1], data[(i<<1) | 1]);
  }

  inline T query(int l, int r) const {
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

  inline pointer operator[](const int idx) {
    return pointer(*this, idx);
  }

  inline T operator[](const int l, const int r) const {
    return query(l, r);
  }

  // f(op([0...i])) == false となる最小の i を返す
  // f(op(a, b)) == f(a) && f(b) となるように設計してください
  inline int bin_search(const function<bool(T)> &f) const {
    auto find = [&](auto&& find, int i, int l, int r, T offset) -> int {
      if (f(op(offset, data[i]))) return r;
      if (l + 1 == r) return l + f(op(offset, data[i]));
      int m = midpoint(l, r);
      int res = find(find, 2 * i, l, m, offset);
      if (res != m) return res;
      return find(find, 2 * i + 1, m, r, op(offset, data[2*i]));
    };
    return find(find, 1, 0, n, e);
  }
};

// template <typename T>
// class SumSegmentTree : public SegmentTree<T> {
// public:
//   SumSegmentTree(const size_t n) : SegmentTree<T>(n, plus<T>(), 0) {}
//   SumSegmentTree(const vec<T> &v) : SegmentTree<T>(v, plus<T>(), 0) {}
// };

// template <typename T>
// class MinSegmentTree : public SegmentTree<T> {
// public:
//   MinSegmentTree(const size_t n) : SegmentTree<T>(n, [](T a,T b) { return min(a, b); }, numeric_limits<T>::max()) {}
//   MinSegmentTree(const vec<T> &v) : SegmentTree<T>(v, [](T a, T b) { return min(a, b); }, numeric_limits<T>::max()) {}
// };

// template <typename T>
// class MaxSegmentTree : public SegmentTree<T> {
// public:
//   MaxSegmentTree(const size_t n) : SegmentTree<T>(n, [](T a, T b) { return max(a, b); }, numeric_limits<T>::min()) {}
//   MaxSegmentTree(const vec<T> &v) : SegmentTree<T>(v, [](T a, T b) { return max(a, b); }, numeric_limits<T>::min()) {}
// };

