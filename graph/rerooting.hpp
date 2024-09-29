#pragma once

#include "template.hpp"

// 重みなし無向木に対する全方位木DP
// res[i] := 頂点iを根と見た時の結果
//
// T: モノイド
// g: 木の隣接リスト
// merge: モノイドのマージ
// add_root: 部分木に根を追加する関数
// e: モノイドの単位元
template<typename T>
vector<T> rerooting(vvec<int> g, const function<T(T,T)>& merge, const function<T(T,int)> add_root, T e) {
  // [i] := root=0として、iを根とする部分木の結果
  vec<T> fwd_dp(g.size());
  auto dfs1 = [&](auto fn, int v, int p) -> T {
    T res = e;
    for (int c : g[v]) {
      if (c == p) continue;
      res = merge(res, fn(fn, c, v));
    }
    return fwd_dp[v] = add_root(res, v);
  };
  dfs1(dfs1, 0, -1);

  // root=0の時に親子関係p->iが存在する時、root=iとして、pを根とした部分木の結果
  vec<T> rev_dp(g.size());
  vec<T> ans(g.size());
  // p, vはroot=0の時の親子関係
  auto dfs2 = [&](auto fn, int v, optional<int> p) -> void {
    // left[i] := [0, i), right[i] := [i, n)
    vector<T> left(g[v].size()+1, e), right(g[v].size()+1, e);
    for(int i=0; i<g[v].size(); ++i) {
      if(g[v][i] == p) left[i+1] = left[i];
      else left[i+1] = merge(left[i], fwd_dp[g[v][i]]);
    }
    for(int i=g[v].size()-1; i>=0; --i) {
      if(g[v][i] == p) right[i] = right[i+1];
      else right[i] = merge(right[i+1], fwd_dp[g[v][i]]);
    }

    ans[v] = left.back();
    if(p) ans[v] = merge(ans[v], rev_dp[v]);
    ans[v] = add_root(ans[v], v);

    for(int i=0; i<g[v].size(); ++i) {
      if(g[v][i] == p) continue;
      T res = e;
      res = merge(res, left[i]);
      res = merge(res, right[i+1]);
      if(p) res = merge(res, rev_dp[v]);
      rev_dp[g[v][i]] = add_root(res, v);
      fn(fn, g[v][i], v);
    }
  };
  dfs2(dfs2, 0, -1);

  return ans;
}
