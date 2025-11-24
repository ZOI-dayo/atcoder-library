#pragma once

#include "../util/all.hpp"

template <typename T = ll, const T e = 0,
          const auto op = [](ll a, ll b)
          { return a + b; },
          const auto rop = [](ll a, ll b)
          { return a - b; }>
class BIT
{
  int n;
  vec<T> data;

public:

  explicit inline BIT(const int N) : n(N), data(n + 1, e) {}
  explicit inline BIT(const vec<T> &v) : BIT(v.size()) { build(v); }

  inline void build(const vec<T> &v)
  {
    memcpy(&data[1], v.data(), v.size() * sizeof(T));
    reps(i, 1, n + 1)
    {
      int j = i + (i & -i);
      if (j <= n)
        data[j] = op(data[j], data[i]);
    }
  }

  inline void apply(int k, T x)
  {
    for (++k; k <= n; k += k & -k)
      data[k] = op(data[k], x);
  }

  inline T prod(int r) const
  {
    if (r <= 0)
      return e;
    T ret = e;
    for (; r > 0; r -= r & -r)
      ret = op(ret, data[r]);
    return ret;
  }

  inline T prod(int l, int r) const
  {
    if (l >= r)
      return e;
    return rop(prod(r), prod(l));
  }

  // int lower_bound(T x)
  // {
  //   int i = 0;
  //   for (int k = 1 << bit_width(n); k > 0; k >>= 1)
  //   {
  //     if (i + k <= n && data[i + k] < x)
  //     {
  //       x -= data[i + k];
  //       i += k;
  //     }
  //   }
  //   return i;
  // }

  // int upper_bound(T x)
  // {
  //   int i = 0;
  //   for (int k = 1 << bit_width(n); k > 0; k >>= 1)
  //   {
  //     if (i + k <= n && data[i + k] <= x)
  //     {
  //       x -= data[i + k];
  //       i += k;
  //     }
  //   }
  //   return i;
  // }
};
