#pragma once
#include <cassert>
// #include "../common/alias.hpp"
#include "point.hpp"

namespace zoi {
namespace geometry {

class Area {
public:
  int H, W;
  bool allow_outside = false;
  char out_val;
  Area(int H, int W) : H(H), W(W), data(std::vector(H, std::string(W, '.'))) {}
  Area(int H, int W, char out_val)
      : H(H), W(W), data(std::vector(H, std::string(W, '.'))),
        allow_outside(true), out_val(out_val) {}
  std::string &operator[](int i) { return data[i]; }
  // 時計回りで90度回転
  Area rotated90() const {
    Area ret(W, H);
    for (int i = 0; i < H; ++i)
      for (int j = 0; j < W; ++j)
        ret[j][H - i - 1] = data[i][j];
    return ret;
  }
  void rotate90() {
    assert(H == W);
    data = rotated90().data;
  }
  char at(int x, int y) {
    if (contains(x, y))
      return data[x][y];
    else if (allow_outside)
      return out_val;
    else {
      std::cerr << "[Area::at] out of range" << std::endl;
      assert(false);
    }
  }
  void set(int x, int y, char val) {
    if (contains(x, y))
      data[x][y] = val;
    else if (allow_outside)
      return;
    else {
      std::cerr << "[Area::set] out of range" << std::endl;
      assert(false);
    }
  }

  bool contains(int x, int y) const {
    return 0 <= x && x < H && 0 <= y && y < W;
  }
  bool contains(point_t p) const { return contains(p.x, p.y); }

private:
  std::vector<std::string> data;
};
inline std::ostream &operator<<(std::ostream &os, Area &a) {
  for (int i = 0; i < a.H; ++i)
    os << a[i] << std::endl;
  return os;
}
inline std::istream &operator>>(std::istream &is, Area &a) {
  for (int i = 0; i < a.H; ++i)
    is >> a[i];
  return is;
}

} // namespace geometry
} // namespace zoi
