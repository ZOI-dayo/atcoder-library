#pragma once

#include "template.hpp"

template <typename T = ll> vec<ll> dijkstra(WGraph<T> &graph, int start) {
  vec<ll> way(graph.size(), INF);
  rp_queue<WeightState> q;
  q.push(WeightState(start, 0));
  way[start] = 0;
  while (!q.empty()) {
    WeightState current = q.top();
    q.pop();
    for (auto next : graph[current.location]) {
      ll next_cost = current.used_cost + next.cost;
      if (way[next.id] <= next_cost)
        continue;
      way[next.id] = next_cost;
      q.push(WeightState(next.id, way[next.id]));
    }
  }
  return way;
}
