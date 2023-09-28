---
title: Fenwick Tree
documentation_of: ./fenwick-tree.hpp
---

## Method

- `BIT<T> BIT<T>(int n)`  
  $O(n)$  
  N要素の型`T`に対するBITを生成  
- `void add(int i, T val)`  
  $O(\log(n))$  
  指定された値を加算する  
- `T sum(int i)`  
  $O(\log(n))$  
  `[0, i]`の総和を計算する  

## Warning

- $0 \leq i < n$

