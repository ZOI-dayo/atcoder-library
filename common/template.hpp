#pragma once

#include <bits/stdc++.h>

using namespace std;

// --- 型エイリアス ---
using ll = long long;
template <typename T> using vec = vector<T>;
template <typename T> using p_queue = priority_queue<T>;
template <typename T> using rp_queue = priority_queue<T, vec<T>, greater<T>>;

// --- 制御マクロ ---
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define all(v) begin(v), end(v)

// --- 定数 ---
constexpr ll INF = 1LL << 60;

// --- デバッグ ---
#define printd(x) cerr << #x << ": " << x << endl;
