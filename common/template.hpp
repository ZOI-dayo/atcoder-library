#pragma once

#include <bits/stdc++.h>
// #include <gmpxx.h>
#include <boost/multiprecision/cpp_int.hpp>

#include "print.hpp"

using namespace std;
using namespace boost::multiprecision;

// --- 型エイリアス ---
using ll = long long;
template <typename T> using vec = vector<T>;
template <typename T> using vvec = vector<vector<T>>;
template <typename T> using p_queue = priority_queue<T>;
template <typename T> using rp_queue = priority_queue<T, vec<T>, greater<T>>;

// --- 黒魔術 ---
#define int ll

// --- 制御マクロ ---
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define all(v) begin(v), end(v)
#define BIT(n) (1LL << (n))
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
#ifndef ONLINE_JUDGE
// #define printd(x) cerr << #x << ": " << x << endl;
const string _TERM_ESC = "\033";
const string _TERM_BOLD = _TERM_ESC + "[1m";
const string _TERM_DECO_RESET = _TERM_ESC + "[0m";
const string _TERM_FORE_RED = _TERM_ESC + "[31m";
const string _TERM_FORE_RESET = _TERM_ESC + "[39m";
const string _TERM_BACK_RED = _TERM_ESC + "[41m";
const string _TERM_BACK_RESET = _TERM_ESC + "[49m";

#define line_debug() cerr << "line: " << __LINE__ << endl;
#define coutd(x) cerr << "[debug] " << x;
#define printd(x)                                                              \
  cerr << _TERM_BOLD << _TERM_BACK_RED << "[debug] " << #x << " = " << x       \
       << _TERM_BACK_RESET << _TERM_DECO_RESET << endl;

#else

#define line_debug() ;
#define coutd(x) ;
#define printd(x) ;

#endif

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
  return is_contained(0, x, H) && is_contained(0, y, W);
}

// rootに対し、aとbが同じ側にあるか (=は含まない)
bool is_same_side(int root, int a, int b) { return (root < a) == (root < b); }

// vector継承にする?
template <typename T> struct vec_accumulate : vec<T> {
  vec<T> data;
  explicit vec_accumulate(vec<T> &v) : data(v.size()) {
    assert(v.size() > 0);
    data[0] = v[0];
    for (int i = 1; i < v.size(); ++i)
      data[i] = data[i - 1] + v[i];
  }

  T &operator[](int i) {
    assert(is_contained(-1, i, data.size()));
    if (i == -1)
      return T();
    return data[i];
  }
};

void io_setup() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cout << std::fixed << std::setprecision(15);
}
