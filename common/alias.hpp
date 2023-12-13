#pragma once

// #include <gmpxx.h>
// #include <boost/multiprecision/cpp_int.hpp>

#include <bits/stdc++.h>
using namespace std;
// using namespace std::views;
// using namespace boost::multiprecision;

// --- 型エイリアス ---
using ll = long long;
using ull = unsigned long long;
template <typename T> using vec = vector<T>;
template <typename T> using vvec = vector<vector<T>>;
template <typename T> using p_queue = priority_queue<T>;
template <typename T> using rp_queue = priority_queue<T, vec<T>, greater<T>>;

// --- 黒魔術 ---
#define int ll

// --- 制御マクロ ---
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define all(v) begin(v), end(v)
// #define BIT(n) (1LL << (n))
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

inline signed bit_width(ll x) { return bit_width((ull)x); }
inline ull bit_ceil(ll x) { return bit_ceil((ull)x); }
