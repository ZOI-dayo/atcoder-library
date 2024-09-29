#pragma once

#include "../std/util.hpp"

#include <stack>
#include <vector>

namespace zoi {
  namespace graph {

    template <typename T = long long> struct wedge_t {
      int to;
      T cost;

      wedge_t(int to, T cost) : to(to), cost(cost) {}
    };

    namespace __diameter {

      [[nodiscard]]
      inline int diameter(const std::vector<std::vector<int>>& graph,
                          const int start = 0) {
        std::vector<int> seen(graph.size(), 0);

        struct result_t {
          int cost;
          int index;

          bool operator<(const result_t& rhs) const { return cost < rhs.cost; }
        };

        auto dfs = [&](auto fn, int index) -> result_t {
          result_t result = {0, index};
          seen[index] = 1;
          for (auto next : graph[index]) {
            if (seen[next]) continue;
            auto next_result = fn(fn, next);
            next_result.cost += 1;
            result = util::max(result, next_result);
          }
          seen[index] = 0;
          return result;
        };
        auto result = dfs(dfs, start);
        result = dfs(dfs, result.index);
        return result.cost;
      }

      template <typename T = long long>
      [[nodiscard]]
      int diameter(std::vector<std::vector<T>>& graph, int start = 0) {
        struct result_t {
          T cost;
          int index;
        };

        auto dfs = [&](int index) -> result_t {
          std::vector<T> result(graph.size(), -1);

          T mx = 0;
          int mx_index = index;
          std::stack<int> st;
          st.push(index);
          result[index] = 0;
          while (!st.empty()) {
            int current = st.top();
            st.pop();
            for (auto next : graph[current]) {
              if (result[next.id] >= 0) continue;
              st.push(next.id);
              result[next.id] = result[current] + next.cost;
              if (chmax(mx, result[next.id])) mx_index = next.id;
            }
          }
          return {mx, mx_index};
        };
        auto result = dfs(start);
        result = dfs(result.second);
        return result.first;
      }
    } // namespace __diameter

    using __diameter::diameter;

  } // namespace graph
} // namespace zoi
