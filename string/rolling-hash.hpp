#pragma once

#include "../math/modint.hpp"

template <int MOD = 1000000007> class RollingHash {
  using mint = modint<MOD>;

public:
  static vec<mint> mod;
  static mint base;

  mint hash;
  int length;

  RollingHash() : hash(0), length(0) {}
  explicit RollingHash(char c) : hash((int)c), length(1) {}
  explicit RollingHash(mint hash, int length) : hash(hash), length(length) {}

  inline RollingHash append(char c) const {
    return RollingHash<MOD>(hash * base + mint((int)c), length + 1);
  }
  static inline RollingHash append(RollingHash h, char c) {
    return h.append(c);
  }
  inline RollingHash merge(RollingHash b) const {
    extend_pow(length + b.length);
    return RollingHash<MOD>(hash * mod[b.length] + b.hash, length + b.length);
  }
  static inline RollingHash merge(RollingHash a, RollingHash b) {
    return a.merge(b);
  }

  static inline void extend_pow(int new_length) {
    int old_length = mod.size();
    if (new_length < old_length)
      return;
    mod.resize(new_length + 1);
    for (int i = old_length; i <= new_length; i++) {
      mod[i] = mod[i - 1] * base;
    }
  }
};

template <int MOD>
vec<modint<MOD>> RollingHash<MOD>::mod = vec<modint<MOD>>(1, modint<MOD>(1));

template <int MOD> modint<MOD> RollingHash<MOD>::base = modint<MOD>(1007);

template <int MOD = 1000000007> class RollingHashedString {
  using RH = RollingHash<MOD>;
  vec<RH> hashes;

public:
  explicit inline RollingHashedString(string s) : hashes(s.size() + 1) {
    RH::extend_pow(s.size());
    rep(i, s.size()) { hashes[i + 1] = RH::append(hashes[i], s[i]); }
  }

  inline RH query(int l, int r) const {
    assert(0 <= l);
    assert(l <= r);
    assert(r <= (int)hashes.size() - 1);
    RH::extend_pow(r - l);
    return RH(hashes[r].hash - hashes[l].hash * RH::mod[r - l], r - l);
  }

  inline int length() const { return hashes.size() - 1; }
};
