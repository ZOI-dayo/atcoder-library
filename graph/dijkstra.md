---
title: Dijkstra (単一始点最短経路)
documentation_of: ./dijkstra.hpp
---

## Method

- `vec<ll> dijkstra(WGraph &graph, int start)`
  $O(N+M)$ (N頂点M辺)  
  負の辺を持たない重み付きグラフに対して、`ans[i] := startとiの最短経路の長さ`となる配列を返す

