#pragma once

#include <cassert>
#include <iostream>
#include <vector>

namespace zoi {
namespace datastructure {

template <typename T> struct imos {
private:
  const int _n;
  std::vector<T> _data;
  bool _is_build = false;

public:
  explicit imos(int n) : _n(n), _data(_n + 1, 0) {}
  explicit imos(std::vector<T> src) : _n(src.size()), _data(_n + 1, 0) {
    for (int i = 0; i < _n; ++i)
      add(i, src[i]);
  }
  inline int size() const { return _n; }
  inline void add(int l, int r, T x) {
    assert(!_is_build);
    assert(l < r);
    assert(0 <= l && r <= _n);
    _data[l] += x;
    _data[r] -= x;
  }
  inline void add(int i, T x) {
    assert(!_is_build);
    assert(0 <= i && i < _n);
    add(i, i + 1, x);
  }
  inline void build() {
    for (int i = 0; i < _n; ++i)
      _data[i + 1] += _data[i];
    _is_build = true;
  }
  inline T get(int i) {
    assert(0 <= i && i < _n);
    if (!_is_build)
      build();
    return _data[i];
  }

  friend std::ostream &operator<<(std::ostream &os, const imos<T> &a) {
    if (!a._is_build) {
      os << "not builded";
      return os;
    }
    os << a._data;
    return os;
  }
};

} // namespace datastructure
} // namespace zoi
