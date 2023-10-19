---
title: imos Vector
documentation_of: ./imos.hpp
---

## Description

imos法。累積和の応用...?

区間加算クエリを$O(1)$で処理できる。  
すべての更新クエリが終わってから累積和を取ることで、値を求められるようになる。

## Tips

- 一度`build()`すると、それ以後の変更はできないようになっています。

## Usage

| Method | Cost | Verifyed | Description |
| :--- | :--- | :--- |
| `(int n) -> imos<T>`      | $O(1)$           | :heavy_check_mark: | 長さ`n`のimosを生成 |
| `(vec<T> src) -> imos<T>` | $O(N)$           | :warning:          | 配列をimosに変換 |
| `size() -> int`           | $O(1)$           | :warning:          | 配列の長さ |
| `add(int l, int r, T x)`  | $O(1)$           | :heavy_check_mark: | 半開区間[l, r)に値xを加算 |
| `add(int i, T x)`         | $O(1)$           | :warning:          | インデックスiに値xを加算 |
| `build()`                 | $O(N)$           | :heavy_check_mark: | 累積和を計算、そして配列をロック |
| `get(int i) -> T`         | $O(1)$ or $O(N)$ | :heavy_check_mark: | 指定された要素を取得 <br> 必要ならば`build()`を呼び出す |

```cpp
imos<int> imos(N);
rep(i, M) {
  imos.add(L[i], R[i] + 1, 1);
}
imos.build();
cout << imos.get(K) << endl;
```

## Assets

- [作者の解説](https://imoz.jp/algorithms/imos_method.html)
