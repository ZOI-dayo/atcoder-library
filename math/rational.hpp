#include "../common/template.hpp"

template <typename T = ll>
struct Rational {
  T num, den;
  Rational(T num, T den) : num(num), den(den) {
    T g = gcd(num, den);
    this->num /= g;
    this->den /= g;
  }
  Rational operator+(const Rational& rhs) const {
    return Rational(num * rhs.den + rhs.num * den, den * rhs.den);
  }
  Rational operator-(const Rational& rhs) const {
    return Rational(num * rhs.den - rhs.num * den, den * rhs.den);
  }
  Rational operator*(const Rational& rhs) const {
    return Rational(num * rhs.num, den * rhs.den);
  }
  Rational operator/(const Rational& rhs) const {
    return Rational(num * rhs.den, den * rhs.num);
  }

  bool operator<(const Rational& rhs) const {
    return num * rhs.den < rhs.num * den;
  }
  bool operator>(const Rational& rhs) const {
    return num * rhs.den > rhs.num * den;
  }
  bool operator==(const Rational& rhs) const {
    return num * rhs.den == rhs.num * den;
  }
  bool operator!=(const Rational& rhs) const {
    return !(*this == rhs);
  }
  bool operator<=(const Rational& rhs) const {
    return (*this < rhs) || (*this == rhs);
  }
  bool operator>=(const Rational& rhs) const {
    return (*this > rhs) || (*this == rhs);
  }
  friend ostream& operator<<(ostream& os, const Rational& r) {
    return os << r.num << "/" << r.den;
  }

  double val() const {
    return (double)num / den;
  }
};
