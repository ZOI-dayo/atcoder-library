#pragma once

#include "../common/alias.hpp"
#include "pow.hpp"

// ミラーラビン素数判定法
// O(k log^3 n)
// https://drken1215.hatenablog.com/entry/2023/05/23/233000
bool MillerRabin(long long N, vector<long long> A) {
    long long s = 0, d = N - 1;
    while (d % 2 == 0) {
        ++s;
        d >>= 1;
    }
    for (auto a : A) {
        if (N <= a) return true;
        long long t, x = mod_pow(a, d, N);
        if (x != 1) {
            for (t = 0; t < s; ++t) {
                if (x == N - 1) break;
                x = __int128_t(x) * x % N;
            }
            if (t == s) return false;
        }
    }
    return true;
}

bool is_prime(long long N) {
    if (N <= 1) return false;
    if (N == 2) return true;
    if (N % 2 == 0) return false;
    if (N < 4759123141LL)
        return MillerRabin(N, {2, 7, 61});
    else
        return MillerRabin(N, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
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
  left.insert(left.end(), all(right));
  sort(all(left), [](const PrimeFactor &a, const PrimeFactor &b) {
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
