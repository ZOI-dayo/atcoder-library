#pragma once

#include "../common/alias.hpp"
#include "../math/modint.hpp"
#include "./ntt.hpp"

template <int MOD>
vec<modint998> convolution(vec<modint998> f, vec<modint998> g) {
  using mint = modint998;

  vec<mint> nf, ng;
  size_t size = bit_ceil(f.size() + g.size() - 1);
  nf.resize(size);
  ng.resize(size);
  rep(i, f.size()) {
    nf[i] = f[i];
    ng[i] = g[i];
  }
  // ntt::translate(nf);
  // ntt::translate(ng);
  rep(i, size) { nf[i] *= ng[i]; }
  dft(nf, true);
  vec<mint> res;
  res.reserve(size);
  rep(i, size) res.emplace_back(nf[i].real() / size);
  return res;
}

// TODO: https://sen-comp.hatenablog.com/entry/2021/02/06/180310
