#pragma once

#include "../std/util.hpp"

#include <iostream>
#include <vector>

namespace zoi {
  namespace math {

    namespace _modint {

      constexpr inline int32_t normalize(int val, int32_t mod) {
        return (val % mod + mod) % mod;
      }

      constexpr inline int32_t inv(int32_t a, int32_t mod) {
        int32_t b = mod, u = 1, v = 0;
        while (b) {
          int32_t t = a / b;
          a -= t * b;
          std::swap(a, b);
          u -= t * v;
          std::swap(u, v);
        }
        u %= mod;
        if (u < 0) u += mod;
        return u;
        // return mod_pow(val, mod - 2, mod);
      }

      template <int MOD> struct dynamic_modint {
      private:
        int _val;

      public:
        dynamic_modint() : dynamic_modint(0) {}

        dynamic_modint(int val) : _val(normalize(val, MOD)) {}

        // logic
        int val() const { return _val; }

        inline dynamic_modint inv() const {
          return dynamic_modint(inv(_val, MOD));
        }

        inline dynamic_modint pow(const int n) const {
          return dynamic_modint(util::powm(_val, n, MOD));
        }

        inline static constexpr dynamic_modint pow(const dynamic_modint& a,
                                                   const int n) {
          return dynamic_modint(mod_pow(a._val, n, a.MOD));
        }

        // op
        inline dynamic_modint& operator++() { return *this += 1; }

        inline dynamic_modint& operator--() { return *this -= 1; }

        inline dynamic_modint operator++(int32_t) const {
          dynamic_modint tmp = *this;
          ++*this;
          return tmp;
        }

        inline dynamic_modint operator--(int32_t) {
          dynamic_modint tmp = *this;
          --*this;
          return tmp;
        }

        inline dynamic_modint operator+(const dynamic_modint& a) const {
          return dynamic_modint(_val) += a;
        }

        inline dynamic_modint operator-(const dynamic_modint& a) const {
          return dynamic_modint(_val) -= a;
        }

        inline dynamic_modint operator*(const dynamic_modint& a) const {
          return dynamic_modint(_val) *= a;
        }

        inline dynamic_modint operator/(const dynamic_modint& a) const {
          return dynamic_modint(_val) /= a;
        }

        inline bool operator==(const dynamic_modint& a) {
          return _val == a._val;
        }

        inline bool operator!=(const dynamic_modint& a) {
          return _val != a._val;
        }

        inline dynamic_modint& operator+=(const dynamic_modint& a) {
          _val += a.val();
          if (_val >= MOD) _val -= MOD;
          return *this;
        }

        inline dynamic_modint& operator-=(const dynamic_modint& a) {
          _val -= a.val();
          if (_val < 0) _val += MOD;
          return *this;
        }

        inline dynamic_modint& operator*=(const dynamic_modint& a) {
          _val = _val * a.val() % MOD;
          return *this;
        }

        inline dynamic_modint& operator/=(const dynamic_modint& a) {
          *this *= inv(a.val(), MOD);
          return *this;
        }

        explicit operator int() const { return _val; }

        // io
        friend std::ostream& operator<<(std::ostream& os,
                                        const dynamic_modint& a) {
          return os << a._val;
        }

        friend std::istream& operator>>(std::istream& os, dynamic_modint& a) {
          os >> a._val;
          a._val = normalize(a._val, MOD);
          return os;
        }
      };

      template <const int32_t MOD> struct modint {
      private:
        using i32 = int32_t;
        i32 _val;

      public:
        consteval inline modint() noexcept : _val(0) {}

        constexpr inline modint(int val) noexcept : _val(normalize(val, MOD)) {}

        constexpr inline modint(const modint& val) noexcept : _val(val._val) {}

        // logic
        constexpr i32 val() const noexcept { return _val; }

        constexpr modint pow(const int n) const {
          return modint(util::powm(_val, n, MOD));
        }

        constexpr inline static modint pow(const modint& a,
                                           const int n) noexcept {
          return modint(mod_pow(a._val, n, a.MOD));
        }

        constexpr inline modint inv() const noexcept {
          return modint(inv(_val, MOD));
        }

        // op
        constexpr inline modint& operator++() noexcept { return *this += 1; }

        constexpr inline modint& operator--() noexcept { return *this -= 1; }

        constexpr inline modint operator++(int32_t) noexcept {
          modint tmp = *this;
          ++*this;
          return tmp;
        }

        constexpr inline modint operator--(int32_t) noexcept {
          modint tmp = *this;
          --*this;
          return tmp;
        }

        constexpr inline modint operator+(const modint& a) const noexcept {
          return modint(*this) += a;
        }

        constexpr inline modint operator-(const modint& a) const noexcept {
          return modint(*this) -= a;
        }

        constexpr inline modint operator*(const modint& a) const noexcept {
          return modint(*this) *= a;
        }

        constexpr inline modint operator/(const modint& a) const noexcept {
          return modint(*this) /= a;
        }

        constexpr inline bool operator==(const modint& a) const noexcept {
          return _val == a.val();
        }

        constexpr inline bool operator!=(const modint& a) const noexcept {
          return _val != a.val();
        }

        constexpr inline modint& operator+=(const modint& a) noexcept {
          _val += a._val;
          if (_val >= MOD) _val -= MOD;
          return *this;
        }

        constexpr inline modint& operator-=(const modint& a) noexcept {
          _val -= a._val;
          if (_val < 0) _val += MOD;
          return *this;
        }

        constexpr inline modint& operator*=(const modint& a) noexcept {
          _val = (int64_t)_val * a._val % MOD;
          return *this;
        }

        constexpr inline modint& operator/=(const modint& a) noexcept {
          *this *= inv(a.val(), MOD);
          return *this;
        }

        explicit operator int() const noexcept { return _val; }

        // io
        friend std::ostream& operator<<(std::ostream& os,
                                        const modint& a) noexcept {
          return os << a._val;
        }

        friend std::istream& operator>>(std::istream& os, modint& a) noexcept {
          os >> a._val;
          a._val = normalize(a._val, MOD);
          return os;
        }
      };

    } // namespace _modint

    template <int MOD> using dynamic_modint = _modint::dynamic_modint<MOD>;
    template <int MOD> using modint = _modint::modint<MOD>;

    template <int MOD>
    std::ostream& operator<<(std::ostream& os, const dynamic_modint<MOD>& i) {
      os << i.val();
      return os;
    }

    template <int MOD>
    std::ostream& operator<<(std::ostream& os,
                             const std::vector<dynamic_modint<MOD>>& v) {
      for (int i = 0; i < (int)v.size(); i++)
        os << v[i].val() << (i + 1 != (int)v.size() ? " " : "");
      return os;
    }

    using mint998 = modint<998244353>;

  } // namespace math
} // namespace zoi
