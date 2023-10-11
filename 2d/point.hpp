#pragma once
#include "../common/template.hpp"

class Point {
public:
  int x, y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}

  Point up() { return Point(x, y - 1); }
  Point down() { return Point(x, y + 1); }
  Point left() { return Point(x - 1, y); }
  Point right() { return Point(x + 1, y); }

  vec<Point> around4() { return {up(), down(), left(), right()}; }
  vec<Point> around8() {
    return {up(),   up().right(),  right(), right().down(),
            down(), down().left(), left(),  left().up()};
  }

  int manhattan() const { return std::abs(x) + std::abs(y); }

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

  Point operator+(const Point &p) const {
    return Point(x + p.x, y + p.y);
  }
  Point operator-(const Point &p) const {
    return Point(x - p.x, y - p.y);
  }
};
ostream &operator<<(ostream &os, const Point &p) {
  os << p.x << p.y;
  return os;
}
istream &operator>>(istream &is, Point &p) {
  is >> p.x >> p.y;
  return is;
}
