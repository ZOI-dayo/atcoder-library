#pragma once

#include "template.hpp"

struct TreeNodeInfo {
public:
  TreeNodeInfo(int parent, int depth) : parent(parent), depth(depth) {}
  int parent;
  int depth;
};

vec<TreeNodeInfo> depth(Graph &graph, int root = 0) {
  vec<TreeNodeInfo> result(graph.size(), TreeNodeInfo(-1, -1));
  stack<int> st;
  st.push(root);
  result[root] = TreeNodeInfo(root, 0);
  while(!st.empty()) {
    int index = st.top();
    st.pop();
    for (auto next : graph[index]) {
      if (result[next].depth != -1)continue;
      result[next] = TreeNodeInfo(index, result[index].depth + 1);
      st.push(next);
    }
  }
  return result;
}
