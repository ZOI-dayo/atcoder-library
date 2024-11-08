#pragma once

#include "util/all.hpp"
#include "segment-tree/monoid.hpp"

template <MonoidConcept M>
class SegmentTree {
private:
  using T = typename M::value_type;
  int n;
  vector<T> data;
  M monoid;

public:
  inline SegmentTree(size_t _n) : n(bit_ceil(_n)), monoid(M()) {
    data.assign(2 * n, monoid.e());
  }

  inline SegmentTree(vec<T> v) : SegmentTree(v.size()) {
    rep(i, v.size()) data[i + n] = v[i];
    for (int i = n - 1; i > 0; --i)
      data[i] = monoid.op(data[2 * i], data[2 * i + 1]);
  }

  inline T get(size_t i) {
    return data[i + n];
  }

  inline T set(size_t i, T x) {
    i += n;
    data[i] = x;
    for (i /= 2; i > 0; i /= 2) {
      data[i] = monoid.op(data[2 * i], data[2 * i + 1]);
    }
    return data[1];
  }

  inline T query(size_t l, size_t r) {
    T res_l = monoid.e(), res_r = monoid.e();
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l % 2 == 1) {
        res_l = monoid.op(res_l, data[l++]);
      }
      if (r % 2 == 1) {
        res_r = monoid.op(data[--r], res_r);
      }
    }
    return monoid.op(res_l, res_r);
  }

  inline T operator[](size_t i) {
    return get(i);
  }

  inline T operator[](size_t l, size_t r) {
    return query(l, r);
  }

};
