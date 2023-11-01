#pragma once

#include "../common/template.hpp"
#include "./pow.hpp"

template <int MOD> struct modint {
private:
  int _val;

public:
  modint() : modint(0) {}
  modint(int val) : _val(val) { normalize(); }

  // logic
  int val() const { return _val; }
  void normalize() { _val = (_val % MOD + MOD) % MOD; };
  modint inv() const {
    int a = _val, b = MOD, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return modint(u);
  }
  modint pow(const int n) const { return modint(mod_pow(_val, n, MOD)); }
  static constexpr modint pow(const modint &a, const int n) {
    return modint(mod_pow(a._val, n, a.MOD));
  }

  // op
  inline modint &operator++() { return *this += 1; }
  inline modint &operator--() { return *this -= 1; }
  modint operator++(int32_t) const {
    modint tmp = *this;
    ++*this;
    return tmp;
  }
  modint operator--(int32_t) {
    modint tmp = *this;
    --*this;
    return tmp;
  }
  modint operator+(const modint &a) const { return modint(_val) += a; }
  modint operator-(const modint &a) const { return modint(_val) -= a; }
  modint operator*(const modint &a) const { return modint(_val) *= a; }
  modint operator/(const modint &a) const { return modint(_val) /= a; }
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
    _val = _val * a._val % MOD;
    return *this;
  }
  modint &operator/=(const modint &a) {
    *this *= a.inv();
    return *this;
  }

  explicit operator int() const { return _val; }

  // io
  friend ostream &operator<<(ostream &os, const modint &a) {
    return os << a._val;
  }
  friend istream &operator>>(istream &os, modint &a) {
    os >> a._val;
    a.normalize();
    return os;
  }
};

// using modint998 = modint<998244353>;

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

struct modint998 {
private:
  constexpr static const int MOD = 998244353;
  int _val;

public:
  constexpr inline modint998(int val = 0) noexcept : _val(val) { normalize(); }
  constexpr inline modint998(modint998 const &val) noexcept : _val(val._val) {}

  // logic
  constexpr uint32_t val() const noexcept { return _val; }
  constexpr inline void normalize() noexcept {
    _val = (_val % MOD + MOD) % MOD;
  }
  constexpr inline modint998 inv() const noexcept {
    uint32_t a = _val, b = MOD, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return modint998(u);
  }
  constexpr modint998 pow(const int n) const { return modint998(mod_pow(_val, n, MOD)); }
  constexpr inline static modint998 pow(const modint998 &a,
                                        const int n) noexcept {
    return modint998(mod_pow(a._val, n, a.MOD));
  }

  // op
  constexpr inline modint998 &operator++() noexcept { return *this += 1; }
  constexpr inline modint998 &operator--() noexcept { return *this -= 1; }
  constexpr inline modint998 operator++(int32_t) noexcept {
    modint998 tmp = *this;
    ++*this;
    return tmp;
  }
  constexpr inline modint998 operator--(int32_t) noexcept {
    modint998 tmp = *this;
    --*this;
    return tmp;
  }
  constexpr inline modint998 operator+(const modint998 &a) const noexcept {
    return modint998(*this) += a;
  }
  constexpr inline modint998 operator-(const modint998 &a) const noexcept {
    return modint998(*this) -= a;
  }
  constexpr inline modint998 operator*(const modint998 &a) const noexcept {
    return modint998(*this) *= a;
  }
  constexpr inline modint998 operator/(const modint998 &a) const noexcept {
    return modint998(*this) /= a;
  }
  constexpr inline bool operator==(const modint998 &a) noexcept {
    return _val == a._val;
  }
  constexpr inline bool operator!=(const modint998 &a) noexcept {
    return _val != a._val;
  }
  constexpr inline modint998 &operator+=(const modint998 &a) noexcept {
    _val += a._val;
    if (_val >= MOD)
      _val -= MOD;
    return *this;
  }
  constexpr inline modint998 &operator-=(const modint998 &a) noexcept {
    _val -= a._val;
    if (_val < 0)
      _val += MOD;
    return *this;
  }
  constexpr inline modint998 &operator*=(const modint998 &a) noexcept {
    _val = _val * a._val % MOD;
    return *this;
  }
  constexpr inline modint998 &operator/=(const modint998 &a) noexcept {
    *this *= a.inv();
    return *this;
  }

  explicit operator int() const noexcept { return _val; }

  // io
  friend ostream &operator<<(ostream &os, const modint998 &a) noexcept {
    return os << a._val;
  }
  friend istream &operator>>(istream &os, modint998 &a) noexcept {
    os >> a._val;
    a.normalize();
    return os;
  }
};
using mint998 = modint998;
