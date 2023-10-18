#pragma once

#include "../common/alias.hpp"
#include "pow.hpp"

// ミラーラビン素数判定法
// O(k log^3 n)
// https://qiita.com/Kiri8128/items/eca965fe86ea5f4cbb98
bool is_prime(const uint64_t &N) {
  if (N <= 1)
    return false;
  const vec<uint64_t> ws =
      N < 4'759'123'141
          ? vec<uint64_t>{2, 7, 61}
          : vec<uint64_t>{2, 325, 9375, 28178, 450775, 9780504, 1795265022ULL};

  if (N == 2)
    return true;
  if (~N & 1)
    return false;

  uint64_t d = N - 1;
  while (d % 2 == 0)
    d /= 2;
  uint64_t e = 1, rev = N - 1;
  for (uint64_t w : ws) {
    if (w % N == 0)
      continue;
    uint64_t t = d;
    uint64_t y = mod_pow(w, t, N);
    while (t != N - 1 && y != e && y != rev)
      y = y * y % N, t *= 2;
    if (y != rev && t % 2 == 0)
      return false;
  }
  return true;
}

// ポラード・ロー素因数分解法
// 値が大きい場合に有効、ちゃんと調べる!
// O(n^(1/4))
// https://lpha-z.hatenablog.com/entry/2023/01/15/231500
// https://algo-method.com/tasks/553/editorial
uint64_t pollard_rho(uint64_t N) {
  if (N % 2 == 0)
    return 2;
  if (is_prime(N))
    return N;

  uint64_t step = 0;
  auto f = [&](uint64_t x) -> uint64_t {
    return (__int128_t(x) * x + step) % N;
  };
  while (true) {
    ++step;
    uint64_t x = step, y = f(x);
    while (true) {
      uint64_t p = gcd(y - x + N, N);
      if (p == 0 || p == N)
        break;
      if (p != 1)
        return p;
      x = f(x);
      y = f(f(y));
    }
  }
}

// 素因数分解
// https://algo-method.com/tasks/553/editorial
struct PrimeFactor {
  uint64_t prime;
  uint64_t exp;
};
vec<PrimeFactor> prime_factorize(uint64_t N) {
  if (N == 1)
    return {};
  uint64_t p = pollard_rho(N);
  if (p == N)
    return {{p, 1}};
  auto left = prime_factorize(p);
  auto right = prime_factorize(N / p);
  left.insert(left.end(), right.begin(), right.end());
  sort(left.begin(), left.end(), [](const PrimeFactor &a, const PrimeFactor &b) {
    return a.prime < b.prime;
  });
  vec<PrimeFactor> ans;
  rep(i, left.size()) {
    if (i == 0 || left[i].prime != left[i - 1].prime)
      ans.emplace_back(left[i]);
    else
      ans.back().exp += left[i].exp;
  }
  return ans;
}
