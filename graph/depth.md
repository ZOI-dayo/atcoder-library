---
title: グラフの深さ
documentation_of: ./depth.hpp
---

## Type

- `struct TreeNodeInfo`
  重み無し木の各頂点に対して算出される情報  
  - `int parent`
    その頂点の親  
    ただし親が存在しない場合`-1`  
  - `int depth`
    その頂点と根の経路の長さ  

## Method

- `vec<TreeNodeInfo> depth(Graph &graph, int root = 0)`  
  $O(N)$ (N頂点)  
  重み無し木`graph`の各頂点に関して、`TreeNodeInfo`を算出する  

