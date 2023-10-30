#pragma once

#include "../common/alias.hpp"
#include "../math/modint.hpp"

// https://qiita.com/izu_nori/items/17efc243468b1e1bd2b0
// https://qiita.com/Sen_comp/items/9401382df736e51564c1

class ntt {
private:
  static ntt *instance;
  ntt() : ws(DIVIDE_LIMIT + 1), iws(DIVIDE_LIMIT + 1) { generate_zeta(); };
  void generate_zeta() {
    rep(i, DIVIDE_LIMIT + 1) {
      ws[i] = mod_pow(ROOT, 1LL << (DIVIDE_LIMIT - i), MOD);
      iws[i] = mod_pow(ws[i], MOD - 2, MOD);
    }
    /*
    ws[DIVIDE_LIMIT] = mod_pow(PRIMITIVE_ROOT, (MOD - 1) / mod_pow(2, 23,
    998244353), 998244353);//99..なら119乗 iws[DIVIDE_LIMIT] = 1 /
    ws[DIVIDE_LIMIT]; for (int i = DIVIDE_LIMIT - 1; i >= 0; i--) { ws[i] = ws[i
    + 1] * ws[i + 1]; iws[i] = iws[i + 1] * iws[i + 1];
    }
    */
  }
  template <typename T> constexpr T powMod(T p, T n, T m) {
    T res = 1;
    while (n) {
      if (n & 1)
        res = (res * p) % m;
      p = (p * p) % m;
      n >>= 1;
    }
    return (res + m) % m;
  }

  template <typename T> const int bitLength(T i) {
    int res = 0;
    while (i) {
      i >>= 1;
      res++;
    }
    return res;
  }

public:
  // using mint = modint998;
  static const int MOD = 998244353;
  static const int PRIMITIVE_ROOT = 3;
  static const int ROOT = 31;         // Q
  static const int DIVIDE_LIMIT = 23; // M
  vec<int> ws, iws;
  static ntt &get_instance() {
    if (!instance) {
      instance = new ntt;
    }
    return *instance;
  }
  void calc(vec<ll> &A) {
    if (A.size() == 1)
      return;
    int n = A.size();
    int k = bitLength(n - 1);
    int r = 1 << (k - 1);
    for (int m = k; m > 0; m--) {
      for (int l = 0; l < n; l += 2 * r) {
        ll wi = 1;
        for (int i = 0; i < r; i++) {
          ll temp = (A[l + i] + A[l + i + r]) % MOD;
          A[l + i + r] = (A[l + i] - A[l + i + r]) * wi % MOD;
          A[l + i] = temp;
          wi = wi * ws[m] % MOD;
        }
      }
      r >>= 1;
    }
  }
  void intt(std::vector<ll> &A) {
    if (A.size() == 1)
      return;
    ll n = A.size();
    int k = bitLength(n - 1);
    int r = 1;
    for (int m = 1; m < k + 1; m++) {
      for (int l = 0; l < n; l += 2 * r) {
        ll wi = 1;
        for (int i = 0; i < r; i++) {
          ll temp = (A[l + i] + A[l + i + r] * wi) % MOD;
          A[l + i + r] = (A[l + i] - A[l + i + r] * wi) % MOD;
          A[l + i] = temp;
          wi = wi * iws[m] % MOD;
        }
      }
      r <<= 1;
    }
    ll ni = powMod(n, MOD - 2, MOD);
    for (int i = 0; i < n; i++) {
      A[i] = A[i] * ni % MOD;
    }
  }
  void polymul(std::vector<ll> &f, std::vector<ll> &g) {
    int m = f.size() + g.size() - 1;
    int n = 1 << bitLength(m - 1);
    for (int i = 0; i < f.size(); i++) {
      f[i] %= MOD;
    }
    for (int i = 0; i < g.size(); i++) {
      g[i] %= MOD;
    }
    f.resize(n, 0);
    g.resize(n, 0);
    calc(f);
    calc(g);
    for (int i = 0; i < n; i++) {
      f[i] = f[i] * g[i] % MOD;
    }
    intt(f);
    for (int i = 0; i < n; i++) {
      f[i] = (f[i] + MOD) % MOD;
    }
    f.resize(m);
  }
  /*
  vec<mint> translate(const vec<mint>& f, const int inverse, const int log2_f,
const int divide_cnt = DEVIDE_LIMIT) { vec<mint> ret; if (f.size() == 1 ||
divide_cnt == 0) { ret.resize(f.size()); mint zeta = 1; for (int i = 0; i <
ret.size(); i++) { mint now = zeta; for (int j = 0; j < f.size(); j++) { ret[i]
+= f[j] * now; now *= zeta;
        }
        zeta *= ((inverse == 1) ? z[0] : iz[0]);
      }
      return ret;
    }

    vec<mint> f1(f.size() / 2), f2(f.size() / 2);
    //f1とf2を作る。
    for (int i = 0; i < f.size() / 2; i++) {
      f1[i] = f[i * 2];
      f2[i] = f[i * 2 + 1];
    }

    vec<mint> f1_dft = translate(f1, inverse, log2_f - 1, divide_cnt  -1),
f2_dft = translate(f2, inverse, log2_f - 1, divide_cnt - 1);
    ret.resize(f.size());
    mint now = 1;

    for (int i = 0; i < f.size(); i++) {
      ret[i] = f1_dft[i % f1_dft.size()] + now * f2_dft[i % f2_dft.size()];
      now *= ((inverse == 1) ? z[log2_f] : iz[log2_f]);
    }
    return ret;
  }

  vec<mint> calc(const vec<mint>& _f, const vec<mint>& _g) {
    auto f = _f, g = _g;

    //fとgの次数の和以上の最小の2冪-1を次数とする。
    int max_dim = 1, log2_max_dim = 0;
    while (f.size() + g.size() > max_dim) max_dim <<= 1, log2_max_dim++;
    f.resize(max_dim), g.resize(max_dim);
    //多項式fとgのDFT結果を求める。 O(n log n)
    auto f_dft = translate(f, 1, log2_max_dim), g_dft = translate(g, 1,
log2_max_dim);

    //f*gのDFT結果は各f_dftとg_ftの係数の積。O(n)
    vec<mint> fg_dft(max_dim);
    for (int i = 0; i < max_dim; i++) {
        fg_dft[i] = f_dft[i] * g_dft[i];
    }

    //fg_dftをDFT
    auto fg = translate(fg_dft, -1, log2_max_dim);

    //最後にmax_dimで割る
    for (int i = 0; i < fg.size(); i++) {
        fg[i] = fg[i] / max_dim;
    }

    fg.resize(_f.size() + _g.size() - 1);
    return fg;
}
*/
};

ntt *ntt::instance = nullptr;
