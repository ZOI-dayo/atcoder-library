---
title: SegmentTree
documentation_of: ./segment-tree.hpp
---

## Description

セグメント木。二分木上にモノイドを配置し、それぞれの部分の演算結果をキャッシュすることで、範囲取得クエリを$\log(N)$で処理できる。
テンプレートとして[MonoidConcept](./monoid/monoid.hpp)を受け取る。

## Usage

| Method | Cost | Verified | Description |
| `(int n) -> SegmentTree<M>`     | $O(N)$                      | :heavy_check_mark: | 長さNのSegTreeを生成          |
| `(vec<T> &v) -> SegmentTree<M>` | $O(N) \times O(M::op)$      | :warning:          | vectorを元にしてSegTreeを生成 |
| `set(int i, T a)`               | $O(\log N) \times O(M::op)$ | :heavy_check_mark: | インデックスiの値を更新       |
| `get(int i) -> T`               | $O(1)$                      | :warning:          | インデックスiの値を取得       |
| `query(int l, int r) -> T`      | $O(\log N) \times O(M::op)$ | :heavy_check_mark: | 半開区間[l, r)の総積を取得    |

```cpp
SegmentTree<Monoids::MinMonoid<int>> seg(N);
seg.set(i, a);
cout << seg.query(l, r) << endl;
```

