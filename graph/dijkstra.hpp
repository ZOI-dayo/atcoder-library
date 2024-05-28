#pragma once

#include "template.hpp"

template <typename T = ll> vec<T> dijkstra(WGraph<T> &graph, int start) {
  vec<T> way(graph.size(), INF);
  rp_queue<WeightState<T>> q;
  q.push(WeightState<T>(start, 0));
  way[start] = 0;
  while (!q.empty()) {
    WeightState current = q.top();
    q.pop();
    for (auto &next : graph[current.location]) {
      T next_cost = current.used_cost + next.cost;
      if (way[next.id] <= next_cost)
        continue;
      way[next.id] = next_cost;
      q.push(WeightState<T>(next.id, way[next.id]));
    }
  }
  return way;
}
