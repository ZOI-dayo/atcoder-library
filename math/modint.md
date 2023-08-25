---
title: modint
documentation_of: ./modint.hpp
---

**NoVerify**

## Method

- `modint modint()`  
  $O(1)$ NoVerify  
  値0のmodintを生成する  
- `modint modint(int val)`  
  $O(1)$ NoVerify  
  値`val`のmodintを生成する  
- `int val()`  
  $O(1)$ NoVerify  
  modを取った値を返す  
- `int inv()`  
  $O(\log(MOD))$ NoVerify  
  現在のval, MODに対して逆元を計算する  
- `++modint | --modint | modint++ | modint--`  
  $O(1)$ NoVerify  
- `modint + modint | - | *`  
  $O(1)$ NoVerify  
- `modint / modint`  
  $O(\log(mod))$ NoVerify  
- `ostream << modint`  
  $O(1)$ NoVerify  

