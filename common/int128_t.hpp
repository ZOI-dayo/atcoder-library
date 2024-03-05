#pragma once

#include "alias.hpp"

using int128_t = __int128_t;
using uint128_t = __uint128_t;
using lll = int128_t;
using ulll = uint128_t;

// https://kenkoooo.hatenablog.com/entry/2016/11/30/163533

ostream &operator<<(ostream &dest, lll value) {
  ostream::sentry s(dest);
  if (s) {
    lll tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
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

lll string_to_lll(string &s) {
  lll ret = 0;
  for (int i = 0; i < s.length(); i++)
    if ('0' <= s[i] && s[i] <= '9')
      ret = 10 * ret + s[i] - '0';
  return ret;
}

istream &operator>>(istream &src, lll &value) {
  string s;
  src >> s;
  value = string_to_lll(s);
  return src;
}
