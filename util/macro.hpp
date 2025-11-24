#pragma once

#include "std.hpp"
#include "types.hpp"

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define rep(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define reps(i, l, r) for (ll i = (ll)(l); i < (ll)(r); ++i)
#define rrep(i, l, r) for (ll i = (ll)(r) - 1; i >= l; --i)

constexpr ll INF = 1LL<<60;
