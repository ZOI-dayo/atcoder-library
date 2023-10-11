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
