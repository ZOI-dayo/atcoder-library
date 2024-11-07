#pragma once

#include "./std.hpp"

#define ll long long
#define ld long double

template <typename T>
using vec = vector<T>;

template <typename T>
using vvec = vector<vector<T>>;

template <typename T>
using vvvec = vector<vector<vector<T>>>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define rep(i, n) for (ll i = 0; i < (ll)(n); ++i)

constexpr int INF = 1<<30;
constexpr ll LLINF = 1LL<<60;
