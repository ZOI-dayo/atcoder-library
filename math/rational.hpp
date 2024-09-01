#include "../common/alias.hpp"

template <typename T = ll> struct Rational {
  T num, den;
  Rational(T num) : num(num), den(1) {}
  Rational(T num, T den) : num(num), den(den) {
    T g = gcd(num, den);
    this->num /= g;
    this->den /= g;
  }
  Rational operator+(const Rational &rhs) const {
    return Rational(num * rhs.den + rhs.num * den, den * rhs.den);
  }
  Rational operator-(const Rational &rhs) const {
    return Rational(num * rhs.den - rhs.num * den, den * rhs.den);
  }
  Rational operator*(const Rational &rhs) const {
    return Rational(num * rhs.num, den * rhs.den);
  }
  Rational operator/(const Rational &rhs) const {
    return Rational(num * rhs.den, den * rhs.num);
  }

  bool operator<(const Rational &rhs) const {
    return num * rhs.den < rhs.num * den;
  }
  bool operator>(const Rational &rhs) const {
    return num * rhs.den > rhs.num * den;
  }
  bool operator==(const Rational &rhs) const {
    return num * rhs.den == rhs.num * den;
  }
  bool operator!=(const Rational &rhs) const { return !(*this == rhs); }
  bool operator<=(const Rational &rhs) const {
    return (*this < rhs) || (*this == rhs);
  }
  bool operator>=(const Rational &rhs) const {
    return (*this > rhs) || (*this == rhs);
  }
  friend ostream &operator<<(ostream &os, const Rational &r) {
    return os << r.num << "/" << r.den;
  }
  void operator+=(const Rational &rhs) { *this = *this + rhs; }
  void operator-=(const Rational &rhs) { *this = *this - rhs; }
  void operator*=(const Rational &rhs) { *this = *this * rhs; }
  void operator/=(const Rational &rhs) { *this = *this / rhs; }

  double val() const { return (double)num / den; }
  // operator double() const { return val(); }
  // operator string() const { return to_string(num) + "/" + to_string(den); }
  Rational pow(ll n) const {
    if (n == 0) {
      return Rational(1);
    } else if (n < 0) {
      return Rational(den, num).pow(-n);
    } else {
      Rational res = pow(n / 2);
      res *= res;
      if (n % 2 == 1) {
        res *= *this;
      }
      return res;
    }
  }
};
