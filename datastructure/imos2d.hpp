#pragma once

#include "../2d/point.hpp"
#include "../common/alias.hpp"

template <typename T> struct imos2d {
private:
  const int _H, _W;
  vvec<T> _data;
  bool _is_build = false;

public:
  explicit imos2d(int H, int W)
      : _H(H), _W(W), _data(_H + 1, vec<T>(_W + 1, 0)) {}
  explicit imos2d(vvec<T> src)
      : _H(src.size()), _W(src[0].size()), _data(_H + 1, vec<T>(_W + 1, 0)) {
    rep(x, _H) rep(y, _W) add({x, y}, src[x][y]);
  }
  inline pair<int, int> size() const { return {_H, _W}; }
  // 半開区間
  inline void add(Point a, Point b, T x) {
    assert(!_is_build);
    assert(a.x < b.x && a.y < b.y);
    assert(is_contained(_H, _W, a) && is_contained(_H, _W, b.upper_left()));
    _data[a.x][a.y] += x;
    _data[a.x][b.y] -= x;
    _data[b.x][a.y] -= x;
    _data[b.x][b.y] += x;
  }
  inline void add(Point a, T x) {
    assert(!_is_build);
    assert(is_contained(_H, _W, a));
    add(a, a.lower_right(), x);
  }
  inline void build() {
    rep(x, _H) rep(y, _W) _data[x][y + 1] += _data[x][y];
    rep(y, _W) rep(x, _H) _data[x + 1][y] += _data[x][y];
    _is_build = true;
  }
  inline T get(Point p) const {
    assert(is_contained(_H, _W, p));
    assert(_is_build);
    return _data[p.x][p.y];
  }
};

template <typename T> ostream &operator<<(ostream &os, const imos2d<T> &im) {
  rep(x, im.size().first) {
    rep(y, im.size().second) { os << im.get({x, y}) << " "; }
    os << endl;
  }
  return os;
}
