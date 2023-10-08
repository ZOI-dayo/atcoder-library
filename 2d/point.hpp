#pragma once
#include "../common/template.hpp"

class Point {
public:
  int x, y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}

  int manhattan() const { return std::abs(x) + std::abs(y); }

  const Point operator+(const Point &rhs) const {
    return Point(x + rhs.x, y + rhs.y);
  }
  const Point operator-(const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y);
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
