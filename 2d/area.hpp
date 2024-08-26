#pragma once
#include "../common/alias.hpp"
#include "point.hpp"

class Area {
public:
  int H, W;
  bool allow_outside = false;
  char out_val;
  Area(int H, int W) : H(H), W(W), data(vector(H, string(W, '.'))) {}
  Area(int H, int W, char out_val)
      : H(H), W(W), data(vector(H, string(W, '.'))), allow_outside(true),
        out_val(out_val) {}
  string &operator[](int i) { return data[i]; }
  // 時計回りで90度回転
  Area rotated90() const {
    Area ret(W, H);
    rep(i, H) rep(j, W) ret[j][H - i - 1] = data[i][j];
    return ret;
  }
  void rotate90() {
    assert(H == W);
    data = rotated90().data;
  }
  char at(int x, int y) {
    if (is_contained(H, W, x, y))
      return data[x][y];
    else if (allow_outside)
      return out_val;
    else {
      cerr << "[Area::at] out of range" << endl;
      assert(false);
    }
  }
  void set(int x, int y, char val) {
    if (is_contained(H, W, x, y))
      data[x][y] = val;
    else if (allow_outside)
      return;
    else {
      cerr << "[Area::set] out of range" << endl;
      assert(false);
    }
  }

  bool contains(int x, int y) const { return is_contained(H, W, x, y); }
  bool contains(Point p) const { return is_contained(H, W, p.x, p.y); }

private:
  vec<string> data;
};
ostream &operator<<(ostream &os, Area &a) {
  rep(i, a.H) os << a[i] << endl;
  return os;
}
istream &operator>>(istream &is, Area &a) {
  rep(i, a.H) is >> a[i];
  return is;
}
