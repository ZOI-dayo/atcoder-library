#pragma once

#include "../common/template.hpp"
#include "./pow.hpp"

template <int MOD> struct modint {
private:
  int _val;

public:
  modint() : modint(0) {}
  modint(int val) : _val(val) {}

  // logic
  int val() { return _val; }
  int inv() {
    int a = _val, b = MOD, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    u %= MOD;
    if (u < 0)
      u += MOD;
    return u;
  }
  modint pow(int n) { return modint(mod_pow(_val, n, MOD)); }

  // op
  modint &operator++() { return *this += 1; }
  modint &operator--() { return *this -= 1; }
  modint operator++(int32_t) {
    modint tmp = *this;
    ++*this;
    return tmp;
  }
  modint operator--(int32_t) {
    modint tmp = *this;
    --*this;
    return tmp;
  }
  modint operator+(const modint &a) { return *this += a; }
  modint operator-(const modint &a) { return *this -= a; }
  modint operator*(const modint &a) { return *this *= a; }
  modint operator/(const modint &a) { return *this /= a; }
  bool operator==(const modint &a) { return _val == a._val; }
  bool operator!=(const modint &a) { return _val != a._val; }
  modint &operator+=(const modint &a) {
    _val += a._val;
    if (_val >= MOD)
      _val -= MOD;
    return *this;
  }
  modint &operator-=(const modint &a) {
    _val -= a._val;
    if (_val < 0)
      _val += MOD;
    return *this;
  }
  modint &operator*=(const modint &a) {
    _val = (int)((long long)_val * a._val % MOD);
    return *this;
  }
  modint &operator/=(const modint &a) {
    _val = (int)((long long)_val * a.inv()._val % MOD);
    return *this;
  }

  // io
  friend ostream &operator<<(ostream &os, const modint &a) {
    return os << a._val;
  }
};

using modint998 = modint<998244353>;

template <int MOD> ostream &operator<<(ostream &os, const modint<MOD> &i) {
  os << i.val();
  return os;
}

template <int MOD>
ostream &operator<<(ostream &os, const vector<modint<MOD>> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i].val() << (i + 1 != (int)v.size() ? " " : "");
  }
  return os;
}
