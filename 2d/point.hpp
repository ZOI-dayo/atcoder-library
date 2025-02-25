#pragma once

#include "util/all.hpp"

template <typename T>
class Point {
public:
  T x, y;
  Point() : x(0), y(0) {}
#define DEF_CPP_DUMP_2
  Point(T x, T y) : x(x), y(y) {}
  explicit Point(const pair<T, T>& p) : x(p.first), y(p.second) {}

  Point up() const { return Point(x - 1, y); }
  Point down() const { return Point(x + 1, y); }
  Point left() const { return Point(x, y - 1); }
  Point right() const { return Point(x, y + 1); }
  Point up_left() const { return Point(x - 1, y - 1); }
  Point up_right() const { return Point(x - 1, y + 1); }
  Point down_left() const { return Point(x + 1, y - 1); }
  Point down_right() const { return Point(x + 1, y + 1); }

  array<Point, 4> around4() const {
    return {up(), down(), left(), right()};
  }
  array<Point, 8> around8() const {
    return {up(), down(), left(), right(), up_left(), up_right(), down_left(), down_right()};
  }
  
  T manhatttan() const {
    return abs(x) + abs(y);
  }
  T manhattan(const Point& p) const {
    return abs(x - p.x) + abs(y - p.y);
  }
  T euclid2() const {
    return x * x + y * y;
  }
  T euclid2(const Point& p) const {
    return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
  }

  auto operator<=>(const Point& p) const = default;

  Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  void operator+=(const Point& p) {
    x += p.x;
    y += p.y;
  }
  void operator-=(const Point& p) {
    x -= p.x;
    y -= p.y;
  }
};

template<class T>
ostream& operator<<(ostream& os, const Point<T>& p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}

template<class T>
istream& operator>>(istream& is, Point<T>& p) {
  is >> p.x >> p.y;
  return is;
}
