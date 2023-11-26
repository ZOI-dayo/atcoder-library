#pragma once

#include "template.hpp"

int diameter(Graph &graph, int start = 0) {
  vec<int> seen(graph.size(), 0);
  auto dfs = [&](auto fn, int index) -> pair<int, int> {
    // max-cost, index
    pair<int, int> result = {0, index};

    seen[index] = 1;

    for (auto next : graph[index]) {
      if (seen[next])
        continue;
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

template <typename T = ll> int diameter(WGraph<T> &graph, int start = 0) {
  auto dfs = [&](int index) -> pair<T, int> {
    vec<T> result(graph.size(), -1);

    T mx = 0;
    int mx_index = index;
    stack<int> st;
    st.push(index);
    result[index] = 0;
    while (!st.empty()) {
      int current = st.top();
      st.pop();
      for (auto next : graph[current]) {
        if (result[next.id] >= 0)
          continue;
        st.push(next.id);
        result[next.id] = result[current] + next.cost;
        if (chmax(mx, result[next.id])) {
          mx_index = next.id;
        }
      }
    }
    return {mx, mx_index};
  };
  auto result = dfs(start);
  result = dfs(result.second);
  return result.first;
}
