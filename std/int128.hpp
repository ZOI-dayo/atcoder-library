#pragma once

#include <iostream>
#include <string>

namespace zoi {
  namespace int128 {

    using int128_t = __int128_t;
    using uint128_t = __uint128_t;
    using lll = int128_t;
    using ulll = uint128_t;

    // https://kenkoooo.hatenablog.com/entry/2016/11/30/163533

    inline std::ostream& operator<<(std::ostream& dest, int128_t value) {
      std::ostream::sentry s(dest);
      if (s) {
        int128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char* d = std::end(buffer);
        do {
          --d;
          *d = "0123456789"[tmp % 10];
          tmp /= 10;
        } while (tmp != 0);
        if (value < 0) {
          --d;
          *d = '-';
        }
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len)
          dest.setstate(std::ios_base::badbit);
      }
      return dest;
    }

    inline int128_t string_to_lll(std::string& s) {
      int128_t ret = 0;
      for (int i = 0; i < s.length(); i++)
        if ('0' <= s[i] && s[i] <= '9') ret = 10 * ret + s[i] - '0';
      return ret;
    }

    inline std::istream& operator>>(std::istream& src, int128_t& value) {
      std::string s;
      src >> s;
      value = string_to_lll(s);
      return src;
    }

  } // namespace int128
} // namespace zoi
