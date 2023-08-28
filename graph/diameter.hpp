#include "template.hpp"

int diameter(Graph &graph, int start = 0) {
  vec<int> seen(graph.size(), 0);
  auto dfs = [&](auto fn, int index) -> pair<int, int> {
    // max-cost, index
    pair<int, int> result = {0, index};

    seen[index] = 1;

    for (auto next : graph[index]) {
      if (seen[next]) continue;
      auto next_result = fn(fn, next);
      next_result.first += 1;
      result = max(result, next_result);
    }
    seen[index] = 0;
    return result;
  };
  auto result = dfs(dfs, start);
  result = dfs(dfs, result.second);
  return result.first;
}

int diameter(WGraph &graph, int start = 0) {
  vec<int> seen(graph.size(), 0);
  auto dfs = [&](auto fn, int index) -> pair<int, int> {
    // max-cost, index
    pair<int, int> result = {0, index};

    seen[index] = 1;

    for (auto next : graph[index]) {
      if (seen[next.id]) continue;
      auto next_result = fn(fn, next.id);
      next_result.first += next.cost;
      result = max(result, next_result);
    }
    seen[index] = 0;
    return result;
  };
  auto result = dfs(dfs, start);
  result = dfs(dfs, result.second);
  return result.first;
}
