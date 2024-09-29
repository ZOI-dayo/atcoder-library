#pragma once

#include <vector>

namespace zoi {
namespace graph {

[[nodiscard]]
inline bool has_cycle(const std::vector<std::vector<int>> &g,
                      const int start = 0) {
  std::vector<int> seen(g.size(), 0);
  std::vector<int> finished(g.size(), 0);
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

} // namespace graph
} // namespace zoi
