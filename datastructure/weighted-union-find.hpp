#pragma once

#include "../common/template.hpp"

template <addable T>
struct WeightedUnionFind {
private:
  int _n;
  vec<int> _parents;
  vec<int> _size;
  vec<T> _weight;

  T weight(int i) {
    find(i);
    return _weight[i];
  }

public:
  explicit WeightedUnionFind(int n) : _n(n), _parents(n), _size(n, 1), _weight(n) {
    iota(all(_parents), 0);
  }

  int find(int i) {
    if (_parents[i] == i)
      return i;
    const int root = find(_parents[i]);
    _weight[i] += _weight[_parents[i]];
    return _parents[i] = root;
  }

  void merge(int a, int b, T w) {
    w += weight(a);
    w -= weight(b);
    a = find(a);
    b = find(b);
    if (a != b) {
      // merge後の親はa
      if (_size[a] < _size[b])
        swap(a, b), w = -w;
      _size[a] += _size[b];
      _size[b] = 0;
      _parents[b] = a;
      _weight[b] = w;
    }
  }

  T diff(int a, int b) { return weight(b) - weight(a); }

  int size(int a) { return _size[find(a)]; }

  bool same(int a, int b) { return find(a) == find(b); }
};

template <addable T>
using WUF = WeightedUnionFind<T>;
