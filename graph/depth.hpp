#pragma once

#include <stack>
#include <vector>

namespace zoi {
namespace graph {
namespace __depth {

struct node_t {
public:
  node_t(int parent, int depth) : parent(parent), depth(depth) {}
  int parent;
  int depth;
};

[[nodiscard]]
inline std::vector<node_t> depth(const std::vector<std::vector<int>> &graph,
                                 const int root = 0) {
  std::vector<node_t> result(graph.size(), node_t(-1, -1));
  std::stack<int, std::vector<int>> st;
  st.push(root);
  result[root] = node_t(root, 0);
  while (!st.empty()) {
    int index = st.top();
    st.pop();
    for (auto next : graph[index]) {
      if (result[next].depth != -1)
        continue;
      result[next] = node_t(index, result[index].depth + 1);
      st.push(next);
    }
  }
  return result;
}
} // namespace __depth

using __depth::depth;

} // namespace graph
} // namespace zoi
