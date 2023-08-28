---
title: LCA - Lowest Common Ancestor (最小共通祖先)
documentation_of: ./lca.hpp
---

## Method
- `LCA(Graph &graph, int root = 0)`  
  $O(N\log(N))$ (N頂点)  
  重み無し木`graph`に対し、LCAの前処理を行う  
- `int query(int u, int v)`  
  $O(\log(N))$ (N頂点)  
  頂点`u`、`v`のLCAを返す

