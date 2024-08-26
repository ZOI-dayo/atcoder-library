#pragma once
#include "../common/alias.hpp"
#include "../common/util.hpp"

class Point {
public:
  int x, y;
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}

  Point up() const { return Point(x - 1, y); }
  Point down() const { return Point(x + 1, y); }
  Point left() const { return Point(x, y - 1); }
  Point right() const { return Point(x, y + 1); }
  Point upper_left() const { return Point(x - 1, y - 1); }
  Point upper_right() const { return Point(x - 1, y + 1); }
  Point lower_left() const { return Point(x + 1, y - 1); }
  Point lower_right() const { return Point(x + 1, y + 1); }

  vec<Point> around4() const { return {up(), down(), left(), right()}; }
  vec<Point> around8() const {
    return {up(),   up().right(),  right(), right().down(),
            down(), down().left(), left(),  left().up()};
  }

  int manhattan() const { return std::abs(x) + std::abs(y); }
  int eucurid2() const { return x * x + y * y; }

  bool operator==(const Point &p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point &p) const { return !(*this == p); }
  void operator+=(const Point &p) {
    x += p.x;
    y += p.y;
  }
  void operator-=(const Point &p) {
    x -= p.x;
    y -= p.y;
  }

  Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
  Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }

  bool operator<(const Point &p) const { return x == p.x ? y < p.y : x < p.x; }
  bool operator>(const Point &p) const { return x == p.x ? y > p.y : x > p.x; }
};
ostream &operator<<(ostream &os, const Point &p) {
  os << p.x << p.y;
  return os;
}
istream &operator>>(istream &is, Point &p) {
  is >> p.x >> p.y;
  return is;
}

inline bool is_contained(int H, int W, Point p) {
  return is_contained(H, W, p.x, p.y);
}
