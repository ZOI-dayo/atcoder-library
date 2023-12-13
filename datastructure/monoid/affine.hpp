#pragma once

template <class T> class Affine {
public:
  T a, b;
  Affine(T a, T b) : a(a), b(b) {}
  T operator()(T x) const { return a * x + b; }
  Affine operator*(const Affine &rhs) const {
    return Affine(a * rhs.a, b * rhs.a + rhs.b);
  }
  Affine operator+(const Affine &rhs) const { return Affine(a, b + rhs.b); }
  Affine operator-(const Affine &rhs) const { return Affine(a, b - rhs.b); }
  Affine operator-() const { return Affine(-a, -b); }
  Affine operator/(const Affine &rhs) const {
    return Affine(a / rhs.a, b / rhs.a - rhs.b / rhs.a);
  }
  Affine &operator*=(const Affine &rhs) { return *this = *this * rhs; }
  Affine &operator+=(const Affine &rhs) { return *this = *this + rhs; }
  Affine &operator-=(const Affine &rhs) { return *this = *this - rhs; }
  Affine &operator/=(const Affine &rhs) { return *this = *this / rhs; }
  bool operator==(const Affine &rhs) const { return a == rhs.a && b == rhs.b; }
  bool operator!=(const Affine &rhs) const { return !(*this == rhs); }
};
