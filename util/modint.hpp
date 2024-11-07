#pragma once

#include "./all.hpp"

template <int MOD>
class modint {
public:
  int val;
  modint() : val(0) {}
  modint(ll x) : val(x%MOD) {}
  modint operator+(modint x) { return modint(val + x.val); }
  modint operator-(modint x) { return modint(val - x.val + MOD); }
  modint operator*(modint x) { return modint((ll)val * x.val % MOD); }
  modint operator/(modint x) { return *this * x.inv(); }
  modint inv() { return pow_mod(val, MOD-2, MOD); }
};

template <int MOD> istream& operator>>(istream& is, modint<MOD>& x) { ll t; is >> t; x = t; return is; }
template <int MOD> ostream& operator<<(ostream& os, modint<MOD> x) { return os << x.val; }
