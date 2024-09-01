#include "../common/alias.hpp"

class Cuboid {
public:
  int x, y, z;
  int w, h, d;
  Cuboid(int x, int y, int z, int w, int h, int d)
      : x(x), y(y), z(z), w(w), h(h), d(d) {}
  Cuboid(int w, int h, int d) : x(0), y(0), z(0), w(w), h(h), d(d) {}
  int volume() { return w * h * d; }
  Cuboid intersect(Cuboid c) {
    int x1 = max(x, c.x);
    int y1 = max(y, c.y);
    int z1 = max(z, c.z);
    int x2 = min(x + w, c.x + c.w);
    int y2 = min(y + h, c.y + c.h);
    int z2 = min(z + d, c.z + c.d);
    if (x2 <= x1 || y2 <= y1 || z2 <= z1) {
      return Cuboid(0, 0, 0, 0, 0, 0);
    }
    return Cuboid(x1, y1, z1, x2 - x1, y2 - y1, z2 - z1);
  }
  void move(int dx, int dy, int dz) {
    x += dx;
    y += dy;
    z += dz;
  }
  static Cuboid intersect(Cuboid &a, Cuboid &b) { return a.intersect(b); }
  static Cuboid intersect(initializer_list<Cuboid> cuboids) {
    auto it = cuboids.begin();
    Cuboid c = *it;
    it++;
    for (; it != cuboids.end(); it++) {
      c = c.intersect(*it);
    }
    return c;
  }
};
