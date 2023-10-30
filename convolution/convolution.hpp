#pragma once

#include "../common/alias.hpp"
#include "../math/modint.hpp"

// https://qiita.com/izu_nori/items/17efc243468b1e1bd2b0
// https://qiita.com/Sen_comp/items/9401382df736e51564c1

class Convolution {
private:
  static Convolution *instance;
  Convolution() : ws(DIVIDE_LIMIT + 1), iws(DIVIDE_LIMIT + 1) {
    generate_zeta();
  }
  void generate_zeta() {
    rep(i, DIVIDE_LIMIT + 1) {
      ws[i] = mod_pow(ROOT, 1LL << (DIVIDE_LIMIT - i), MOD);
      iws[i] = mod_pow(ws[i], MOD - 2, MOD);
    }
  }

public:
  using mint = mint998;
  static const int MOD = 998244353;
  // static const int PRIMITIVE_ROOT = 3;
  static const int ROOT = 31;         // Q
  static const int DIVIDE_LIMIT = 23; // M
  vec<int> ws, iws;
  static Convolution &get_instance() {
    if (!instance) {
      instance = new Convolution;
    }
    return *instance;
  }
  void ntt(vec<mint> &A) {
    if (A.size() == 1)
      return;
    int n = A.size();
    int k = bit_width(n - 1);
    int r = 1 << (k - 1);
    for (int m = k; m > 0; m--) {
      for (int l = 0; l < n; l += 2 * r) {
        mint wi = 1;
        for (int i = 0; i < r; i++) {
          mint temp = A[l + i] + A[l + i + r];
          A[l + i + r] = (A[l + i] - A[l + i + r]) * wi;
          A[l + i] = temp;
          wi = wi * ws[m];
        }
      }
      r >>= 1;
    }
  }
  void inv_ntt(vec<mint> &A) {
    if (A.size() == 1)
      return;
    ll n = A.size();
    int k = bit_width(n - 1);
    int r = 1;
    for (int m = 1; m < k + 1; m++) {
      for (int l = 0; l < n; l += 2 * r) {
        mint wi = 1;
        for (int i = 0; i < r; i++) {
          mint temp = A[l + i] + A[l + i + r] * wi;
          A[l + i + r] = A[l + i] - A[l + i + r] * wi;
          A[l + i] = temp;
          wi = wi * iws[m];
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
  void calc(vec<mint> &f, vec<mint> &g) {
    int m = f.size() + g.size() - 1;
    int n = 1 << bit_width(m - 1);
    f.resize(n, 0);
    g.resize(n, 0);
    ntt(f);
    ntt(g);
    for (int i = 0; i < n; i++) {
      f[i] = f[i] * g[i];
    }
    inv_ntt(f);
    f.resize(m);
  }
};

Convolution *Convolution::instance = nullptr;

inline void convolution(vec<mint998> &f, vec<mint998> &g) {
  Convolution::get_instance().calc(f, g);
}
