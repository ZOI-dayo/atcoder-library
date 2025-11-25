#pragma once

#include "../util/all.hpp"

template <typename T = ll, const T e = 0,
          const auto op = plus<T>{},
          const auto rop = minus<T>{}>
class BIT
{
  const int n;
  vec<T> data;

public:
  class pointer
  {
  private:
    BIT<T, e, op> &parent;
    const int i;

  public:
    pointer(BIT<T, e, op> &bit, int i) : parent(bit), i(i) {}
    inline operator T() const
    {
      return parent[i, i + 1];
    }
    inline pointer &operator+=(const T &other)
    {
      parent.add(i, other);
      return *this;
    }
  };

  explicit inline BIT(const int N) : n(N), data(n + 1, e) {}
  explicit inline BIT(const vec<T> &v) : BIT(v.size())
  {
    memcpy(&data[1], v.data(), v.size() * sizeof(T));
    reps(i, 1, n + 1)
    {
      int j = i + (i & -i);
      if (j <= n)
        data[j] = op(data[j], data[i]);
    }
  }

  inline void add(int k, T x)
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

  inline pointer operator[](int i)
  {
    return pointer(*this, i);
  }

  inline T operator[](int l, int r) const
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
