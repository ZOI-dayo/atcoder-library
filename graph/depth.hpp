#include "template.hpp"

struct TreeNodeInfo {
public:
  TreeNodeInfo(int parent, int depth) : parent(parent), depth(depth) {}
  int parent;
  int depth;
};

vec<TreeNodeInfo> depth(Graph &graph, int root = 0) {
  vec<TreeNodeInfo> result(graph.size(), TreeNodeInfo(-1,-1));
  auto dfs = [&](auto fn, int index, int parent) -> void {
    result[index] = TreeNodeInfo(parent, result[parent].depth + 1);
    for(auto next : graph[index]) {
      if(result[next].depth != -1) continue;
      fn(fn, next, index);
    }
  };
  dfs(dfs, root, 0);
  return result;
}

vec<TreeNodeInfo> depth(WGraph &graph, int root = 0) {
  vec<TreeNodeInfo> result(graph.size(), TreeNodeInfo(-1, -1));
  auto dfs = [&](auto fn, int index, int parent, int cost) -> void {
    result[index] = TreeNodeInfo(parent, result[parent].depth+ cost);
    for(auto next : graph[index]) {
      if(result[next.id].depth != -1) continue;
      fn(fn, next.id, index, next.cost);
    }
  };
  dfs(dfs, root, 0, -1);
  return result;
}
