#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>

namespace zoi {
  namespace geometry {

    class point_t {
    public:
      int x, y;

      point_t() : x(0), y(0) {}

      point_t(int x, int y) : x(x), y(y) {}

      point_t up() const { return point_t(x - 1, y); }

      point_t down() const { return point_t(x + 1, y); }

      point_t left() const { return point_t(x, y - 1); }

      point_t right() const { return point_t(x, y + 1); }

      point_t upper_left() const { return point_t(x - 1, y - 1); }

      point_t upper_right() const { return point_t(x - 1, y + 1); }

      point_t lower_left() const { return point_t(x + 1, y - 1); }

      point_t lower_right() const { return point_t(x + 1, y + 1); }

      std::vector<point_t> around4() const {
        return {up(), down(), left(), right()};
      }

      std::vector<point_t> around8() const {
        return {up(),   up().right(),  right(), right().down(),
                down(), down().left(), left(),  left().up()};
      }

      int manhattan() const { return std::abs(x) + std::abs(y); }

      int eucurid2() const { return x * x + y * y; }

      bool operator==(const point_t& p) const { return x == p.x && y == p.y; }

      bool operator!=(const point_t& p) const { return !(*this == p); }

      void operator+=(const point_t& p) {
        x += p.x;
        y += p.y;
      }

      void operator-=(const point_t& p) {
        x -= p.x;
        y -= p.y;
      }

      point_t operator+(const point_t& p) const {
        return point_t(x + p.x, y + p.y);
      }

      point_t operator-(const point_t& p) const {
        return point_t(x - p.x, y - p.y);
      }

      bool operator<(const point_t& p) const {
        return x == p.x ? y < p.y : x < p.x;
      }

      bool operator>(const point_t& p) const {
        return x == p.x ? y > p.y : x > p.x;
      }
    };

    inline std::ostream& operator<<(std::ostream& os, const point_t& p) {
      os << p.x << p.y;
      return os;
    }

    inline std::istream& operator>>(std::istream& is, point_t& p) {
      is >> p.x >> p.y;
      return is;
    }

    inline bool is_contained(int H, int W, point_t p) {
      if (p.x < 0 || H <= p.x) return false;
      if (p.y < 0 || W <= p.y) return false;
      return true;
    }

  } // namespace geometry
} // namespace zoi
