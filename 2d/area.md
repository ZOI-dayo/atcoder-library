---
title: 2次元領域
documentation_of: ./area.hpp
---

## Description

stringの二次元領域を扱うためのUtilクラス。  
回転や領域外参照ができる。

## Usage

| Method | Cost | Verifyed | Description |
| :--- | :--- | :--- | :--- |
| `(int H, int W) -> Area`               | $O(HW)$ | :warning: | $H \times W$、初期値`'.'`のAreaを生成 |
| `(int H, int W, char out_val) -> Area` | $O(HW)$ | :warning: | 範囲外参照可能に設定する。out_valには範囲外の値を指定|
| `[] -> string`                         | $O(1)$  | :warning: | 指定されたx座標を返す |
| `rotated90() -> Area`                  | $O(HW)$ | :warning: | 時計回りに90度回転して、その値を返す |
| `rotate90() -> Area`                   | $O(HW)$ | :warning: | 自身を時計回りに90度回転し上書き <br> ただしH=Wである必要がある |
| `at(int x, int y) -> char`             | $O(1)$  | :warning: | 指定された座標の値を取得 |
| `set(int x, int y, char val)`          | $O(1)$  | :warning: | 指定された座標の値を変更 |
| `contains(int x, int y) -> bool`       | $O(1)$  | :warning: | 指定された座標が領域の定義範囲に含まれるかを返す |
| `contains(Point p) -> bool`            | $O(1)$  | :warning: | `contains(x, y)`のPointバージョン |

