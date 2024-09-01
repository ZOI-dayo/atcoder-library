#pragma once

template <typename T> struct imos {
private:
  const int _n;
  vec<T> _data;
  bool _is_build = false;

public:
  explicit imos(int n) : _n(n), _data(_n + 1, 0) {}
  explicit imos(vec<T> src) : _n(src.size()), _data(_n + 1, 0) {
    rep(i, _n) add(i, src[i]);
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
    rep(i, _n) _data[i + 1] += _data[i];
    _is_build = true;
  }
  inline T get(int i) {
    assert(0 <= i && i < _n);
    if (!_is_build)
      build();
    return _data[i];
  }

  friend ostream &operator<<(ostream &os, const imos<T> &a) {
    if (!a._is_build) {
      os << "not builded";
      return os;
    }
    os << a._data;
    return os;
  }
};
