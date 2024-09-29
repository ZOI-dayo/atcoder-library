#pragma once

#include "weighted-graph.hpp"

#include <queue>
#include <vector>

namespace zoi {
  namespace graph {

    namespace _dijkstra {

      template <class T = int64_t> struct state {
      public:
        int location;
        T used_cost;

        state(int location, T used_cost) :
            location(location), used_cost(used_cost) {}

        bool operator<(const state& n) const { return used_cost < n.used_cost; }

        bool operator>(const state& n) const { return used_cost > n.used_cost; }
      };

      template <typename T = int64_t>
      std::vector<T> dijkstra(WGraph<T>& graph, int start) {
        std::vector<T> way(graph.size(), std::numeric_limits<T>::max());
        std::priority_queue<state<T>, std::vector<state<T>>,
                            std::greater<state<T>>>
            q;
        q.push(state<T>(start, 0));
        way[start] = 0;
        while (!q.empty()) {
          state current = q.top();
          q.pop();
          for (auto& next : graph[current.location]) {
            T next_cost = current.used_cost + next.cost;
            if (way[next.id] <= next_cost) continue;
            way[next.id] = next_cost;
            q.push(WeightState<T>(next.id, way[next.id]));
          }
        }
        return way;
      }

    } // namespace _dijkstra

    using _dijkstra::dijkstra;

  } // namespace graph
} // namespace zoi
