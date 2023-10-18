---
title: imos Vector
documentation_of: ./imos.hpp
---

imos法。累積和の応用...?

区間加算クエリを$O(1)$で処理できる。  
すべての更新クエリが終わってから累積和を取ることで、値を求められるようになる。

## Tips

- 一度`build()`すると、それ以後の変更はできないようになっています。

## Methods

| Method | Cost | Description |
| :--- | :--- | :--- |
| `(int n) -> imos<T>` | $O(1)$ | 長さ`n`のimosを生成 |
| `(vec<T> src) -> imos<T>` | $O(N)$ | 配列をimosに変換 |
| `size() -> int` | $O(1)$ | 配列の長さ |
| `add(int l, int r, T x)` | $O(1)$ | 半開区間[l, r)に値xを加算 |
| `add(int i, T x)` | $O(1)$ | インデックスiに値xを加算 |
| `build()` | $O(N)$ | 累積和を計算、そして配列をロック |
| `get(int i) -> T` | $O(1)$ or $O(N)$ | 指定された要素を取得 / 必要ならば`build()`を呼び出す |

## Assets

- [作者の解説](https://imoz.jp/algorithms/imos_method.html)
