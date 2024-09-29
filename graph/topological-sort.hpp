#pragma once

#include <queue>
#include <vector>

namespace zoi {
  namespace graph {

    [[nodiscard]]
    inline std::vector<int>
    topological_sort(const std::vector<std::vector<int>>& graph) {
      std::vector<int> result;
      std::vector<int> deleted(graph.size(), false);

      std::vector<int> in_count(graph.size());
      for (int i = 0; i < graph.size(); ++i)
        for (auto next : graph[i]) in_count[next]++;
      std::queue<int> q;
      for (int i = 0; i < graph.size(); i++)
        if (in_count[i] == 0) q.push(i);

      while (!q.empty()) {
        int now = q.front();
        q.pop();
        result.emplace_back(now);
        deleted[now] = true;
        for (auto next : graph[now]) {
          if (deleted[next]) continue;
          in_count[next]--;
          if (in_count[next] == 0) q.push(next);
        }
      }

      return result;
    }

  } // namespace graph
} // namespace zoi
