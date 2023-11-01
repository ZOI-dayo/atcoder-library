#pragma once

#include "../common/alias.hpp"
#include "../math/modint.hpp"

// https://qiita.com/izu_nori/items/17efc243468b1e1bd2b0
// https://qiita.com/Sen_comp/items/9401382df736e51564c1

namespace Convolution {
using mint = mint998;
constexpr int MOD = 998244353;
constexpr int ROOT = 31;         // Q
constexpr int DIVIDE_LIMIT = 23; // M
// static const int PRIMITIVE_ROOT = 3;
constexpr array<mint, DIVIDE_LIMIT + 1> make_ws() {
  array<mint, DIVIDE_LIMIT + 1> ret;
  generate(all(ret), [n = -1]() mutable {
    return n++, mint(ROOT).pow(1LL << (DIVIDE_LIMIT - n));
  });
  return ret;
}
constexpr auto ws = make_ws();
constexpr array<mint, DIVIDE_LIMIT + 1> make_iws() {
  array<mint, DIVIDE_LIMIT + 1> ret;
  generate(all(ret), [n = -1]() mutable { return n++, ws[n].pow(MOD - 2); });
  return ret;
}
constexpr auto iws = make_iws();

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
  mint ni = mod_pow(n, MOD - 2, MOD);
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
