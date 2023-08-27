#include "template.hpp"

vec<ll> priority_bfs(WGraph &graph, int start){
  vec<ll> way(graph.size(), INF);
  rp_queue<WeightState> q;
  q.push(WeightState(start, 0));
  way[start] = 0;
  while(!q.empty()){
    WeightState current = q.top();
    q.pop();
    for(auto next : graph[current.location]){
      if(way[next.id] <= current.used_cost + next.cost) continue;
      way[next.id] = current.used_cost + next.cost;
      q.push(WeightState(next.id, way[next.id]));
    }
  }
  return way;
}
