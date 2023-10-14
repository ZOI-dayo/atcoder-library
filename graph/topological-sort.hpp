#pragma once

#include "template.hpp"

vec<int> topological_sort(Graph &graph) {
  vec<int> result;
  vec<int> deleted(graph.size(), false);

  vec<int> in_count(graph.size());
  rep(i, graph.size()) {
    for (auto next : graph[i]) {
      in_count[next]++;
    }
  }
  queue<int> q;
  rep(i, graph.size()) {
    if (in_count[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int now = q.front();
    q.pop();
    result.emplace_back(now);
    deleted[now] = true;
    for (auto next : graph[now]) {
      if (deleted[next])
        continue;
      in_count[next]--;
      if (in_count[next] == 0) {
        q.push(next);
      }
    }
  }

  return result;
}
