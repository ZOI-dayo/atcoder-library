---
title: SegmentTree
documentation_of: ./segment-tree.hpp
---

## Method

- `Segtree<T> SegmentTree<T>(int n)`  
  $O(n)$  
  N要素の型`T`に対するRangeMinQueryを実現するセグ木を生成  
- `Segtree<T> SegmentTree<T>(int n, T e, function<T(T, T)> op)`  
  $O(n)$  
  N要素の型`T`に対する、単位元を`e`、演算を`op`とするセグメント木を生成  
- `void set(int i, T a)`  
  $O(\log(n))$  
  セグ木に`seg[i] = a`を書き込む  
- `T get(int i)`  
  $O(1)$  
  `seg[i]`を取得する  
- `T query(int l, int r)`  
  $O(\log(n))$  
  [l, r)の範囲に対して`op`を実行する  

