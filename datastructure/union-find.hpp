#pragma once

#include <numeric>
#include <vector>
#include <algorithm>

namespace zoi {
namespace datastructure {

struct UnionFind {
private:
  int _n;
  std::vector<int> _parents;
  std::vector<int> _size;

public:
  explicit UnionFind(int n) : _n(n), _parents(n), _size(n, 1) {
    iota(_parents.begin(), _parents.end(), 0);
  }
  int find(int a) {
    if (_parents[a] == a)
      return a;
    else
      return _parents[a] = find(_parents[a]);
  }
  void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      // merge後の親はa
      if (_size[a] < _size[b])
        std::swap(a, b);
      _size[a] += _size[b];
      _size[b] = 0;
      _parents[b] = a;
    }
  }
  int size(int a) { return _size[find(a)]; }
  bool same(int a, int b) { return find(a) == find(b); }
  std::vector<std::vector<int>> groups() {
    std::vector<int> leaders(_n);
    for(int i=0; i<_n; ++i) { leaders[i] = find(i); }
    std::vector<std::vector<int>> res(_n);
    for(int i=0; i<_n; ++i) res[i].reserve(_size[i]);
    for(int i=0; i<_n; ++i) res[leaders[i]].push_back(i);
    res.erase(remove_if(res.begin(), res.end(), [&](const std::vector<int> &v) { return v.empty(); }),
              res.end());
    return res;
  }
};
using UF = UnionFind;

} // namespace datastructure
} // namespace zoi
