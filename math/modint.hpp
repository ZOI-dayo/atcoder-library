#pragma once

#include "util/all.hpp"
#include "pow.hpp"

template <int MOD>
class modint {
private:
  int val;
  static int normalize(int x) { return (x % MOD + MOD) % MOD; }
public:
  consteval modint() : val(0) {}
  constexpr modint(ll x) : val(normalize(x)) {}
  constexpr modint operator+(const modint &x) const {
    return modint(val + x.val);
  }
  constexpr modint operator-(const modint &x) const {
    return modint(val - x.val + MOD);
  }
  constexpr modint operator*(const modint &x) const {
    return modint((ll)val * x.val);
  }
  constexpr modint operator/(const modint &x) const {
    return *this * x.inv();
  }
  constexpr modint& operator+=(const modint &x) {
    return *this = *this + x;
  }
  constexpr modint& operator-=(const modint &x) {
    return *this = *this - x;
  }
  constexpr modint& operator*=(const modint &x) {
    return *this = *this * x;
  }
  constexpr modint& operator/=(const modint &x) {
    return *this = *this / x;
  }
  constexpr auto operator<=>(const modint&) const = default;
  constexpr modint& operator++() { return *this += 1; }
  constexpr modint& operator--() { return *this -= 1; }
  constexpr modint operator++(const int) {
    modint res = *this;
    ++*this;
    return res;
  }
  constexpr modint operator--(const int) {
    modint res = *this;
    --*this;
    return res;
  }
  constexpr modint inv() const { return pow_mod(val, MOD-2, MOD); }
  explicit operator int() const { return val; }
  friend istream& operator>>(istream& is, modint& x) { ll t; is >> t; x = t; return is; }
  friend ostream& operator<<(ostream& os, const modint &x) { return os << x.val; }
};

class dynamic_modint {
private:
  int val;
  int MOD;
  static int normalize(int x, int MOD) { return (x % MOD + MOD) % MOD; }

public:
  dynamic_modint() : val(0), MOD(1) {}
  dynamic_modint(ll x, int MOD) : val(normalize(x, MOD)), MOD(MOD) {}

  dynamic_modint operator+(const dynamic_modint &x) const {
    return dynamic_modint(val + x.val, MOD);
  }
  dynamic_modint operator-(const dynamic_modint &x) const {
    return dynamic_modint(val - x.val, MOD);
  }
  dynamic_modint operator*(const dynamic_modint &x) const {
    return dynamic_modint((ll)val * x.val, MOD);
  }
  dynamic_modint operator/(const dynamic_modint &x) const {
    return *this * x.inv();
  }
  dynamic_modint& operator+=(const dynamic_modint &x) {
    return *this = *this + x;
  }
  dynamic_modint& operator-=(const dynamic_modint &x) {
    return *this = *this - x;
  }
  dynamic_modint& operator*=(const dynamic_modint &x) {
    return *this = *this * x;
  }
  dynamic_modint& operator/=(const dynamic_modint &x) {
    return *this = *this / x;
  }
  auto operator<=>(const dynamic_modint&) const = default;
  dynamic_modint& operator++() { return *this += dynamic_modint(1, MOD); }
  dynamic_modint& operator--() { return *this -= dynamic_modint(1, MOD); }
  dynamic_modint operator++(const int) {
    dynamic_modint res = *this;
    ++*this;
    return res;
  }
  dynamic_modint operator--(const int) {
    dynamic_modint res = *this;
    --*this;
    return res;
  }
  dynamic_modint inv() const { return dynamic_modint(pow_mod(val, MOD-2, MOD), MOD); }
  explicit operator int() const { return val; }
  friend istream& operator>>(istream& is, dynamic_modint& x) { ll t; is >> t; x = dynamic_modint(t, x.MOD); return is; }
  friend ostream& operator<<(ostream& os, const dynamic_modint &x) { return os << x.val; }
};
