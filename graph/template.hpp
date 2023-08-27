#include "../common/template.hpp"

// Node
struct WeightedNode {
  int id;
  int cost;
  WeightedNode(int id, int cost) : id(id), cost(cost) {}
};

struct WeightState {
public:
  int location;
  ll used_cost;
  WeightState(int location, ll used_cost)
      : location(location), used_cost(used_cost) {}
  bool operator<(const WeightState &n) const { return used_cost < n.used_cost; }
  bool operator>(const WeightState &n) const { return used_cost > n.used_cost; }
};

// Graph
using Graph = vec<vec<int>>;

using WeightedGraph = vec<vec<WeightedNode>>;
using WGraph = WeightedGraph;

// Field
struct Point {
public:
  int x, y;
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
  // operator
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
};

class Field {
public:
  vec<vec<char>> field;
  int H, W;
  Field(vec<vec<char>> field) : field(field) {
    H = field.size();
    W = field[0].size();
  }
  bool contains(Point p) { return 0 <= p.x && p.x < W && 0 <= p.y && p.y < H; }
};
