---
title: グラフテンプレート
documentation_of: ./template.hpp
---

## Type

- `struct WeightedNode`  
  重み付きグラフの辺を表す構造体  
  - `int id`  
    移動先の頂点のid  
  - `int cost`  
    辺の重み  
- `struct WeightState`  
  根を定めた重み付きグラフに対して定義される情報  
  - `int location`  
    現在の頂点  
  - `ll used_cost`  
    根から現在の頂点までのコスト
- `Graph` (aka `vec<vec<int>>`)  
  重み無しグラフ  
- `WeightedGraph` (aka `WGraph`, `vec<vec<WeightedNode>>`)  
  重み付きグラフ  
- `struct Point`  
  2次元座標を表す構造体  
  - `up()`, `down()`, `left()`, `right()`  
    各方向に1だけ移動した`Point`を返す  
  - `vec<Point> around4()`, `vec<Point> around8`  
    周囲4/8方向への移動後の座標の一覧を返す  
- `struct Field`  
  領域を持つ2次元空間を表す構造体  
  - `int H, W`  
    縦幅/横幅  
  - `bool contains(Point p)`  
    与えられた座標が領域に含まれているかを返す 
