#pragma once

#include "std.hpp"
#include "types.hpp"

struct IOSetup{
  IOSetup() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout << fixed << setprecision(16);
  }
} io_setup;

template <typename T>
struct is_string
{
    static const bool value = false;
};

template <class T, class Traits, class Alloc>
struct is_string<basic_string<T, Traits, Alloc>>
{
    static const bool value = true;
};

template <typename F, typename S>
istream& operator>>(istream& is, pair<F, S>& p) {
  return is >> p.first >> p.second;
}

template <typename C>
requires requires(C container) {
begin(container);
end(container);
next(begin(container));
} && (!is_string<C>::value)
istream& operator>>(istream& is, C& container) {
  for(auto&& x : container) {
    is >> x;
  }
  return is;
}

ostream &operator<<(ostream &dest, lll value) {
  ostream::sentry s(dest);
  if (s) {
    lll tmp = value < 0 ? -value : value;
    char buffer[40];
    char *d = end(buffer);
    do {
      --d;
      *d = "0123456789"[(int)(tmp % 10)];
      tmp /= 10;
    } while (tmp);
    if (value < 0) {
      --d;
      *d = '-';
    }
    int len = end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(ios_base::badbit);
    }
  }
  return dest;
}

lll to_lll(string &s) {
  short sign = 1;
  if(!s.empty() && s.front() == '-') {
    sign = -1;
  }
  lll ret = 0;
  for(auto& c : s)
    if ('0' <= c && c <= '9')
      ret = 10 * ret + sign * (c - '0');
  return ret;
}

istream& operator>>(istream& is, lll& p) {
  string s;
  s.reserve(40);
  is >> s;
  p = to_lll(s);
  return is;
}
