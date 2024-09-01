#pragma once

#include "../math/modint.hpp"

// https://qiita.com/izu_nori/items/17efc243468b1e1bd2b0
// https://qiita.com/Sen_comp/items/9401382df736e51564c1

namespace Convolution {
constinit const int MOD = 998244353;
constinit const int ROOT = 31;         // Q
constinit const int DIVIDE_LIMIT = 23; // M
using mint = modint<MOD>;
// static const int PRIMITIVE_ROOT = 3;
// constinit const auto ws = views::iota(0, DIVIDE_LIMIT + 1) | views::all |
// views::transform([](int n) { return mint(ROOT).pow(1LL << (DIVIDE_LIMIT -
// n)); });
constinit const auto ws = []() {
  array<mint, DIVIDE_LIMIT + 1> ws;
  rep(i, DIVIDE_LIMIT + 1) {
    ws[i] = mint(ROOT).pow(1LL << (DIVIDE_LIMIT - i));
  }
  return ws;
}();
// constinit const auto iws = views::iota(0, DIVIDE_LIMIT + 1) | views::all |
// views::transform([](int n) { return ws[n].pow(MOD - 2); });
constinit const auto iws = []() {
  array<mint, DIVIDE_LIMIT + 1> iws;
  rep(i, DIVIDE_LIMIT + 1) { iws[i] = ws[i].pow(MOD - 2); }
  return iws;
}();

inline void ntt(vec<mint> &A) noexcept {
  if (A.size() == 1)
    return;
  int n = A.size();
  int k = bit_width(n - 1);
  int r = 1 << (k - 1);
  for (int m = k; m > 0; --m) {
    for (int l = 0; l < n; l += 2 * r) {
      mint wi = 1;
      for (int i = 0; i < r; ++i) {
        mint temp = A[l + i] + A[l + i + r];
        A[l + i + r] = (A[l + i] - A[l + i + r]) * wi;
        A[l + i] = temp;
        wi *= ws[m];
      }
    }
    r >>= 1;
  }
}
inline void inv_ntt(vec<mint> &A) noexcept {
  if (A.size() == 1)
    return;
  ll n = A.size();
  int k = bit_width(n - 1);
  int r = 1;
  for (int m = 1; m < k + 1; ++m) {
    for (int l = 0; l < n; l += 2 * r) {
      mint wi = 1;
      for (int i = 0; i < r; ++i) {
        mint temp = A[l + i] + A[l + i + r] * wi;
        A[l + i + r] = A[l + i] - A[l + i + r] * wi;
        A[l + i] = temp;
        wi *= iws[m];
      }
    }
    r <<= 1;
  }
  mint ni = powm(n, MOD - 2, MOD);
  // mint ni = mint(n).pow(MOD - 2);
  for (int i = 0; i < n; i++) {
    A[i] = A[i] * ni;
  }
}
inline void calc(vec<mint> &f, vec<mint> &g) noexcept {
  int m = f.size() + g.size() - 1;
  int n = 1 << bit_width(m - 1);
  f.resize(n, 0);
  g.resize(n, 0);
  ntt(f);
  ntt(g);
  for (int i = 0; i < n; ++i) {
    f[i] *= g[i];
  }
  inv_ntt(f);
  f.resize(m);
}
}; // namespace Convolution

// Convolution *Convolution::instance = nullptr;

inline void convolution(vec<mint998> &f, vec<mint998> &g) {
  Convolution::calc(f, g);
}
