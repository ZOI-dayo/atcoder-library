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

## Detail

### モノイドの指定

SegmentTreeは、モノイド、すなわち「結合法則`a \times (b \times c) = (a \times b) \times c`の成り立つような値と演算の組」が与えられた場合に、その値の配列に対しての「1点更新」および「区間の積」の演算を高速に行うことのできるデータ構造である。

なので、まず構築前に、以下のようなモノイドの定義を受け取らなければ何もできない。

- `T` : モノイドの値の型、実装上はノードの型。
- `op`: `T op(T a, T b)`を満たす関数。積に相当。
- `e` : モノイド`a`に対し、`op(a, e) == a`を満たすような値。単位元。

### 初期化

まずはNより大きい$2^k$で表される数を`_n`とおき、これを実装上の要素数として扱う。
SeegmentTreeの頂点数は`2*_n-1`となるが、実装の簡易化のため、配列は1-indexedで管理することとする。よって、配列`_data`は長さ`2*_n`で生成する。

### `void set(int i, T a)`

更新対象のindexおよび更新先が与えられるので、これを反映させる。

まずは、indexをSegTree上のものに変更する。SegTree上の、要素iを表す葉のindexは`i+_n`である。
葉を更新した場合、影響を受けるのはその先祖となるノードだけである。
ノードiの親は`i>>1`で得られることを用いて、iを登らせながら回す。
親の更新後の値は、左右の子をa, bとして`op(a, b)`である。

(更新がない場合、それ以上の先祖更新はなし、とすれば早くなるのかな? わからない)

### `T get(int i)`

(あまり使わないかもだけれども)
配列の要素iの値を得る。
要素iはSegTree配列上のindex=i+_nであることが分かれば説明不要。

### `T query(int l, int r)`

半開区間[l, r)
