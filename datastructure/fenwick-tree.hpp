#pragma once

#include <vector>

namespace zoi {
namespace datastructure {

template <typename T> struct FenwickTree {
private:
  T _n;
  std::vector<T> _data;

public:
  explicit FenwickTree(T n) : _n(n), _data(n + 1, 0) {}
  explicit FenwickTree(const std::vector<T> &src)
      : _n(src.size()), _data(_n + 1, 0) {
    for (int i = 0; i < _n; ++i)
      add(i, src[i]);
  }

  void add(int i, T val) {
    i++;
    while (i <= _n) {
      _data[i] += val;
      i += i & -i;
    }
  }
  // [0, i]
  int sum(int i) const {
    i++;
    T ans = 0;
    while (i > 0) {
      ans += _data[i];
      i -= i & -i;
    }
    return ans;
  }
  // [l, r)
  int sum(int l, int r) const { return sum(r - 1) - sum(l - 1); }
};

} // namespace datastructure
} // namespace zoi
