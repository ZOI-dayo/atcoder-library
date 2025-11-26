#pragma once

#include "../util/all.hpp"
#include <string_view>

class FastSet
{
  static constexpr int B = 64;

  int n;
  int cnt;
  vv<ull> d;

  inline static int bsf(ull x) { return countr_zero(x); }
  inline static int bsr(ull x) { return 63 - countl_zero(x); }
  inline void build_layers()
  {
    int m = n;
    do
    {
      m = (m + B - 1) / B, d.push_back(vec<ull>(m));
    } while (m != 1);
  }

public:
  // allow [0, n) as content
  inline explicit FastSet(int n) : n(n), cnt(0) { build_layers(); }

  inline explicit FastSet(string_view s, const char target = '1') : n(s.size()), cnt(0)
  {
    build_layers();
    auto &base = d.front();
    for (int i = 0; i < n; ++i)
      if (s[i] == target)
      {
        base[i / B] |= 1ULL << (i % B);
        ++cnt;
      }
    for (size_t level = 1; level < d.size(); ++level)
    {
      auto &prev = d[level - 1];
      auto &cur = d[level];
      for (size_t idx = 0; idx < prev.size(); ++idx)
        if (prev[idx])
          cur[idx / B] |= 1ULL << (idx % B);
    }
  }

  inline bool contains(int i) const
  {
    return (d.front()[i / B] >> (i % B)) & 1;
  }

  inline void insert(int i)
  {
    if (contains(i))
      return;
    ++cnt;
    for (auto &v : d)
    {
      bool f = v[i / B];
      v[i / B] |= 1ULL << (i % B), i /= B;
      if (f)
        break;
    }
  }

  inline void erase(int i)
  {
    if (!contains(i))
      return;
    --cnt;
    for (auto &v : d)
    {
      v[i / B] &= ~(1ULL << (i % B)), i /= B;
      if (v[i])
        break;
    }
  }

  inline int next(int i, const int default_val) const
  {
    for (auto itr = d.cbegin(); itr != d.cend(); ++itr, i = i / B + 1)
    {
      if (i / B >= int(itr->size()))
        break;

      if (ull dd = (*itr)[i / B] >> (i % B); dd)
      {
        i += bsf(dd);
        while (itr != d.cbegin())
          i = i * B + bsf((*--itr)[i]);
        return i;
      }
    }

    return default_val;
  }

  inline int next(int i) const
  {
    return next(i, n);
  }

  inline int prev(int i, int default_val = -1) const
  {
    for (auto itr = d.cbegin(); itr != d.cend() and i >= 0; ++itr, i = i / B - 1)
    {
      if (auto dd = (*itr)[i / B] << (B - 1 - i % B); dd)
      {
        i += bsr(dd) - (B - 1);
        while (itr != d.cbegin())
          i = i * B + bsr((*--itr)[i]);
        return i;
      }
    }

    return default_val;
  }

  inline int min() const { return next(0); }
  inline int max() const { return prev(n - 1); }
  inline int size() const { return cnt; }
  inline bool empty() const { return cnt == 0; }

  inline void clear()
  {
    if (!cnt)
      return;
    cnt = 0;
    auto rec = [&](auto &&self, int dd, int x) -> void
    {
      if (dd)
      {
        for (auto m = d[dd][x]; m;)
        {
          int i = bsf(m);
          m -= 1ULL << i, self(self, dd - 1, x * B + i);
        }
      }
      d[dd][x] = 0;
    };
    rec(rec, d.size() - 1, 0);
  }
};