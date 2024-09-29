#pragma once

#include "../2d/point.hpp"
#include <cassert>
#include <iostream>

namespace zoi {
namespace datastructure {
namespace __imos2d {

using geometory::point_t;

template <typename T> struct imos2d {
private:
  const int _H, _W;
  std::vector<std::vector<T>> _data;
  bool _is_build = false;

public:
  explicit imos2d(int H, int W)
      : _H(H), _W(W), _data(_H + 1, vec<T>(_W + 1, 0)) {}
  explicit imos2d(std::vector<std::vector<T>> src)
      : _H(src.size()), _W(src[0].size()), _data(_H + 1, vec<T>(_W + 1, 0)) {
    for(int x=0; x<_H; ++x) for(int y=0; y<_W; ++y) add({x, y}, src[x][y]);
  }
  inline std::pair<int, int> size() const { return {_H, _W}; }
  // 半開区間
  inline void add(point_t a, point_t b, T x) {
    assert(!_is_build);
    assert(a.x < b.x && a.y < b.y);
    assert(is_contained(_H, _W, a) && is_contained(_H, _W, b.upper_left()));
    _data[a.x][a.y] += x;
    _data[a.x][b.y] -= x;
    _data[b.x][a.y] -= x;
    _data[b.x][b.y] += x;
  }
  inline void add(point_t a, T x) {
    assert(!_is_build);
    assert(is_contained(_H, _W, a));
    add(a, a.lower_right(), x);
  }
  inline void build() {
    for(int x=0; x<_H; ++x) for(int y=0; y<_W; ++y) _data[x][y + 1] += _data[x][y];
    for(int y=0; y<_W; ++y) for(int x=0; x<_H; ++x) _data[x + 1][y] += _data[x][y];
    _is_build = true;
  }
  inline T get(point_t p) const {
    assert(is_contained(_H, _W, p));
    assert(_is_build);
    return _data[p.x][p.y];
  }
};

template <typename T> std::ostream &operator<<(std::ostream &os, const imos2d<T> &im) {
  for(int x=0; x<im.size().first; ++x) {
    for(int y=0; y<im.size().second; ++y) os << im.get({x, y}) << " ";
    os << std::endl;
  }
  return os;
}

} // namespace __imos2d

template <typename T> using imos2d = __imos2d::imos2d<T>;

} // namespace datastructure
} // namespace zoi
