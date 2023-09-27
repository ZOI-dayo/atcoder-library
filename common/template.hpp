#pragma once

#include <bits/stdc++.h>

#include "print.hpp"

using namespace std;

// --- 型エイリアス ---
using ll = int64_t;
template <typename T> using vec = vector<T>;
template <typename T> using vvec = vector<vector<T>>;
template <typename T> using p_queue = priority_queue<T>;
template <typename T> using rp_queue = priority_queue<T, vec<T>, greater<T>>;

// --- 黒魔術 ---
#define int ll

// --- 制御マクロ ---
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define all(v) begin(v), end(v)
#define bit(n) (1LL << (n))
#define MAX(type) numeric_limits<type>::max()
#define MIN(type) numeric_limits<type>::min()
#define yes cout << "Yes" << endl
#define no cout << "No" << endl
#define pb push_back
#define mp make_pair
#define fir first
#define sec second

// --- 定数 ---
constexpr ll INF = 1LL << 60;

// --- デバッグ ---
// #define printd(x) cerr << #x << ": " << x << endl;
const string _TERM_ESC = "\033";
const string _TERM_BOLD = _TERM_ESC + "[1m";
const string _TERM_DECO_RESET = _TERM_ESC + "[0m";
const string _TERM_FORE_RED = _TERM_ESC + "[31m";
const string _TERM_FORE_RESET = _TERM_ESC + "[39m";
const string _TERM_BACK_RED = _TERM_ESC + "[41m";
const string _TERM_BACK_RESET = _TERM_ESC + "[49m";

#define line_debug() cerr << "line: " << __LINE__ << endl;
#define coutd cerr << "[debug] "
#define printd(x)                                                              \
  cerr << _TERM_BOLD << _TERM_BACK_RED << "[debug] " << #x << " = " << x       \
       << _TERM_BACK_RESET << _TERM_DECO_RESET << endl;

// --- Utils ---

// 合計値を求める
ll sum(const vec<ll> &v) { return accumulate(all(v), 0LL); }

// 可変引数min
template <class... T> auto min(T... a) {
  return min(initializer_list<common_type_t<T...>>{a...});
}

// 可変引数max
template <class... T> auto max(T... a) {
  return max(initializer_list<common_type_t<T...>>{a...});
}

template <class T> bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}
template <class T> bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return 1;
  }
  return 0;
}

// 3項間不等式
// 広義単調増加
bool is_increasing(int x, int y, int z) { return x <= y && y <= z; }

// 半開区間[x, z)にyが含まれるか?
bool is_contained(int x, int y, int z) { return x <= y && y < z; }

// 頂点(x, y)が範囲に含まれるか
bool is_contained(int H, int W, int x, int y) {
  return is_increasing(0, x, H) && is_increasing(0, y, W);
}
