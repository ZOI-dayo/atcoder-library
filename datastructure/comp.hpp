#pragma once

#include <cassert>
#include <vector>

// https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/4/DSL_4_A

namespace zoi {
namespace datastructure {

template <typename T> struct comp {
private:
  const int _n;
  int _cmp_n;
  std::vector<T> _raw, _comp;

public:
  explicit comp(const std::vector<T> &src)
      : _n(src.size()), _cmp_n(0), _raw(src), _comp(_n, 0) {
    sort(_raw.begin(), _raw.end());
    _raw.erase(unique(_raw.begin(), _raw.end()), _raw.end());
    _cmp_n = _raw.size();
    for (int i = 0; i < _n; ++i)
      _comp[i] = lower_bound(_raw.begin(), _raw.end(), src[i]) - _raw.begin();
  }
  inline int size() const { return _n; }
  inline int cmp_size() const { return _cmp_n; }
  inline T get_raw(int complessed) {
    assert(0 <= complessed && complessed < _cmp_n);
    return _raw[complessed];
  }
  inline T operator[](int i) {
    assert(0 <= i && i < _n);
    return _comp[i];
  }
  inline T get_comp(int raw) {
    return lower_bound(_raw.begin(), _raw.end(), raw) - _raw.begin();
  }
};

} // namespace datastructure
} // namespace zoi
