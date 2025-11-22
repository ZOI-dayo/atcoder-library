#pragma once

#include "std.hpp"

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template <typename T>
using vec = vector<T>;

template <typename T>
using vv = vector<vector<T>>;

template <typename T>
using vvv = vector<vector<vector<T>>>;

template <typename T>
using p_queue = priority_queue<T>;

template <typename T>
using rp_queue = priority_queue<T, vector<T>, greater<T>>;

using pll = pair<ll, ll>;
using vl = vec<ll>;