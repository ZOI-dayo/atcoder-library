#pragma once

#include "std.hpp"
#include "types.hpp"
#include "ext_lib/boost.hpp"

class FastIn
{
  static const int buf_siz = (1 << 25);
  char buf[buf_siz], *beg, *end;

  // 64bit以下の整数型について、string->numberのパースを行う
  template <typename T>
  inline void parse(T &x)
  {
    uint64_t x2 = 0;
    uint64_t tmp;
    while (1)
    {
      memcpy(&tmp, beg, 8);
      if ((tmp -= 0x3030303030303030) & 0x8080808080808080)
        goto parse_end8;
      tmp = (tmp * 10 + (tmp >> 8)) & 0xff00ff00ff00ff;
      tmp = (tmp * 100 + (tmp >> 16)) & 0xffff0000ffff;
      tmp = (tmp * 10000 + (tmp >> 32)) & 0xffffffff;
      x2 = 1'0000'0000 * x2 + tmp;
      beg += 8;
    }
  parse_end8:
    memcpy(&tmp, beg, 4);
    if ((tmp -= 0x30303030) & 0x80808080)
      goto parse_end4;
    tmp = (tmp * 10 + (tmp >> 8)) & 0xff00ff;
    tmp = (tmp * 100 + (tmp >> 16)) & 0xffff;
    x2 = 10000 * x2 + tmp;
    beg += 4;
  parse_end4:
    memcpy(&tmp, beg, 2);
    if ((tmp -= 0x3030) & 0x8080)
      goto parse_end2;
    tmp = (tmp * 10 + (tmp >> 8)) & 0xff;
    x2 = 100 * x2 + tmp;
    beg += 2;
  parse_end2:
    if (' ' < *beg)
    {
      x2 = x2 * 10;
      x2 = x2 + (*beg++ - '0');
    }
    ++beg;
    x = static_cast<T>(x2);
  }

  inline void seek()
  {
    while (*beg <= ' ')
      ++beg;
  }

public:
  inline FastIn()
  {
    beg = buf;
    end = beg + fread(buf, 1, buf_siz, stdin);
  }

  template <unsigned_integral T>
  inline FastIn &operator>>(T &dst)
  {
    seek();
    parse(dst);
    return *this;
  }

  template <signed_integral T>
  inline FastIn &operator>>(T &dst)
  {
    seek();
    make_unsigned_t<T> u;
    if (*beg == '-')
    {
      ++beg;
      parse(u);
      dst = -static_cast<T>(u);
    }
    else
    {
      parse(u);
      dst = static_cast<T>(u);
    }
    return *this;
  }

  inline FastIn &operator>>(char &dst)
  {
    seek();
    dst = *beg;
    ++beg;
    return *this;
  }

  inline FastIn &operator>>(string &dst)
  {
    seek();
    dst.clear();
    while (*beg > ' ')
    {
      dst.push_back(*beg);
      ++beg;
    }
    return *this;
  }

  template <typename C>
    requires requires(C container) {
      begin(container);
      std::end(container);
      next(begin(container));
    } && (!is_string<C>::value)
  FastIn &operator>>(C &container)
  {
    for (auto &x : container)
    {
      *this >> x;
    }
    return *this;
  }

#ifdef EXIST_BOOST
  inline FastIn &operator>>(bint &dst)
  {
    seek();
    if (*beg == '-')
    {
      ++beg;
      while(*beg > ' ') {
        dst *= 10;
        dst += *beg - '0';
        ++beg;
      }
      dst = -dst;
    }
    else
    {
      while(*beg > ' ') {
        dst *= 10;
        dst += *beg - '0';
        ++beg;
      }
    }
    return *this;
  }

#endif
} fin;

class FastOut
{
  static const int buf_siz = (1 << 25);
  char buf[buf_siz], *beg, *end;

  template <class T>
  static constexpr int DIGITS = numeric_limits<T>::digits10 + 1;

  template <class T>
  static constexpr auto POW10 = []
  {
    array<T, DIGITS<T>> ret;
    ret[0] = 1;
    for (int i = 1; i < DIGITS<T>; ++i)
    {
      ret[i] = 10 * ret[i - 1];
    }
    return ret;
  }();

  // 0000~9999までの配列
  static constexpr auto LUT = []
  {
    array<char, 40000> res;
    char *p = res.data();
    char a = '0', b = '0', c = '0', d = '0';
    do
    {
      *p++ = a, *p++ = b, *p++ = c, *p++ = d;
    } while (d++ < '9' || (d = '0', c++ < '9' || (c = '0', b++ < '9' || (b = '0', a++ < '9'))));
    return res;
  }();

  // 上から最大4桁を出力
  template <typename T, int N = 4>
  inline void write_lt4(const T x)
  {
    if constexpr (1 < N)
    {
      if (x < POW10<T>[N - 1])
      {
        write_lt4<T, N - 1>(x);
        return;
      }
    }
    end = copy_n(&LUT[static_cast<size_t>((x << 2) + 4 - N)], N, end);
  }

  // ちょうど(4の倍数)桁を出力
  template <typename T, int N>
  inline void write_4(const T x)
  {
    if constexpr (0 < N)
    {
      end = copy_n(&LUT[static_cast<size_t>(x / POW10<T>[N - 4] * 4)], 4, end);
      write_4<T, N - 4>(x % POW10<T>[N - 4]);
    }
  }

  // N桁を書き出し
  template <typename T, int N = 0>
  inline void write(const T x)
  {
    if constexpr (N < DIGITS<T>)
    {
      if (POW10<T>[N] <= x)
      {
        write<T, N + 4>(x);
        return;
      }
    }
    write_lt4(x / POW10<T>[N - 4]);
    write_4<T, N - 4>(x % POW10<T>[N - 4]);
  }

  inline void write(const char c)
  {
    *end = c;
    ++end;
  }

  inline void write(const string &s)
  {
    memcpy(end, s.c_str(), s.size());
    end += s.size();
  }

public:
  inline FastOut()
  {
    beg = buf;
    end = buf;
  }
  inline ~FastOut()
  {
    flush();
  }

  inline void flush()
  {
    beg += fwrite(beg, 1, end - beg, stdout);
    fflush(stdout);
  }

#define defout_num(T)                      \
  inline FastOut &operator<<(const T &src) \
  {                                        \
    if (src < 0)                           \
    {                                      \
      write('-');                          \
      write(-src);                         \
    }                                      \
    else                                   \
    {                                      \
      write(src);                          \
    }                                      \
    return *this;                          \
  }

#define defout_num_unsigned(T)             \
  inline FastOut &operator<<(const T &src) \
  {                                        \
    write(src);                            \
    return *this;                          \
  }

  defout_num_unsigned(bool);
  defout_num(short);
  defout_num_unsigned(unsigned short);
  defout_num(int);
  defout_num_unsigned(unsigned int);
  defout_num(long long);
  defout_num_unsigned(unsigned long long);
  defout_num(lll);
  defout_num_unsigned(ulll);

#ifdef EXIST_BOOST
  inline FastOut &operator<<(const bint &src)
  {
    write(src.str());
    return *this;
  }

#endif

#undef defout

  inline FastOut &operator<<(const char &src)
  {
    write(src);
    return *this;
  }

  inline FastOut &operator<<(const string &src)
  {
    write(src);
    return *this;
  }

} fout;