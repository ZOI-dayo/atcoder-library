---
title: UnionFind
documentation_of: ./unionfind.hpp
---

## Method

- `UF UnionFind(int n)`  
  $O(n)$  
  N頂点のUnionFindを生成する  
- `int find(int a)`  
  $O(\alpha(n))$  
  頂点`a`の根となる頂点を返す  
- `void merge(int a, int b)`  
  $O(\alpha(n))$  
  頂点`a`、頂点`b`を連結する  
- `bool same(int a, int b)`  
  $O(\alpha(n))$  
  頂点`a`、頂点`b`が連結かどうかを判定する  
- `int size(int a)`  
  $O(\alpha(n))$  
  頂点`a`の含まれるグループの要素数を出力する  
- `vec<vec<int>> groups()`  
  $O(n)$ NoVerify  
  各連結成分の情報を出力する  
  各配列内は昇順(多分)  

