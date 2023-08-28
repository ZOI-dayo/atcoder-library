#include "template.hpp"

bool has_cycle(Graph &g, int start = 0) {
  vec<int> seen(g.size(), 0);
  vec<int> finished(g.size(), 0);
  auto dfs = [&](auto fn, int index) {
    seen[index] = 1;
    for (auto next : g[index]) {
      if (finished[next])
        continue;
      if (seen[next] && !finished[next])
        return true;
      if (fn(fn, next))
        return true;
    }
    finished[index] = 1;
    return false;
  };
  return dfs(dfs, start);
}
