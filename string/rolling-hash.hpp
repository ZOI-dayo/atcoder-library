#pragma once

#include <cassert>
#include <stdexcept>
#include <vector>

namespace zoi {
namespace string {
namespace rolling_hash {

/**
 * @brief modを法とするべき乗を計算する
 * @param x 底
 * @param n 指数
 * @param mod 法
 * @return x^n mod mod
 */
class PowCache {
public:
  int mod;
  int base;
  std::vector<int> pow;
  PowCache(int mod, int base) : mod(mod), base(base), pow(1, 1) {}

  /**
   * @brief powを必要分延長する
   * @param new_length 必要な長さ 増分ではない
   */
  void extend(int new_length) {
    int old_length = pow.size();
    if (new_length < old_length)
      return;
    pow.resize(new_length + 1);
    for (int l = old_length; l <= new_length; l++) {
      pow[l] = pow[l - 1] * base % mod;
    }
  }
  int get(int n) {
    extend(n);
    return pow[n];
  }
};

/**
 * @brief ローリングハッシュの演算を行う
 */
class Hash {
private:
  PowCache *pow_cache;

public:
  int mod;
  int base;
  int val;
  int length;
  Hash(PowCache *pow_cache, int val, int length)
      : pow_cache(pow_cache), mod(pow_cache->mod), base(pow_cache->base),
        val(val), length(length) {}
  void append(char c) {
    val = (val * base + c) % mod;
    length++;
  }
  Hash appended(char c) const {
    Hash ret(pow_cache, val, length);
    ret.append(c);
    return ret;
  }
  void merge(const Hash &h) {
    if (mod != h.mod || base != h.base) {
      throw std::invalid_argument("mod and base must be same");
    }
    val = (val * pow_cache->get(length) + h.val) % mod;
  }
  Hash merged(const Hash &h) const {
    Hash ret(pow_cache, val, length);
    ret.merge(h);
    return ret;
  }
  Hash operator+(char c) const { return appended(c); }
  Hash operator+(const Hash &h) const { return merged(h); }
  Hash operator+=(char c) {
    append(c);
    return *this;
  }
  Hash operator+=(const Hash &h) {
    merge(h);
    return *this;
  }
  Hash operator-(const Hash &h) const {
    if (mod != h.mod || base != h.base) {
      throw std::invalid_argument("mod and base must be same");
    }
    if (length < h.length) {
      throw std::invalid_argument(
          "length must be greater than or equal to h.length");
    }
    int new_length = length - h.length;
    int new_val = (val - h.val * pow_cache->get(new_length)) % mod;
    if (new_val < 0)
      new_val += mod;
    return Hash(pow_cache, new_val, new_length);
  }
  bool operator==(const Hash &h) const {
    return mod == h.mod && base == h.base && val == h.val;
  }
  bool operator!=(const Hash &h) const { return !(*this == h); }
};
}; // namespace rolling_hash

/**
 * @brief 部分文字列のローリングハッシュの計算を行う
 */
class RollingHash {
  /**
   * ハッシュ値を計算するためのmodとbase
   * [i] := {mod, base}
   */
  static std::vector<rolling_hash::PowCache> pow_cache;
  /**
   * [[i]][[j]] := j文字目までのハッシュ値をmod[[i]]で割った余り
   * jは1-indexed、すなわちi=0は空文字列
   */
  std::vector<std::vector<rolling_hash::Hash>> hashes;

public:
  /**
   * @brief stringからRollingHashを構築する
   *
   * @param s 元の文字列
   */
  explicit inline RollingHash(std::string s) {
    hashes.resize(pow_cache.size());
    for (int i = 0; i < pow_cache.size(); ++i) {
      hashes[i].reserve(s.size() + 1);
      hashes[i].emplace_back(rolling_hash::Hash(&pow_cache[i], 0, 0));
    }
    for (int i = 0; i < pow_cache.size(); ++i) {
      for (int j = 0; j < s.size(); ++j) {
        hashes[i].emplace_back(hashes[i][j] + s[j]);
      }
    }
    rolling_hash::Hash h(&pow_cache[0], 0, 0);
  }

  /**
   * @brief
   * [l, r)のハッシュ値を取得する (0-indexed)
   * 制約: 0 <= l <= r <= length()
   * @param l 左端
   * @param r 右端
   * @return [l, r)のハッシュ値
   */
  inline std::vector<rolling_hash::Hash> query(int l, int r) {
    assert(0 <= l);
    assert(l <= r);
    assert(r <= length());
    std::vector<rolling_hash::Hash> ret;
    ret.reserve(pow_cache.size());
    for (int i = 0; i < pow_cache.size(); ++i) {
      ret.emplace_back(hashes[i][r] - hashes[i][l]);
    }
    return ret;
  }

  /**
   * @brief 文字列の長さを取得する
   *
   * @return int 文字列の長さ
   */
  inline int length() const { return hashes[0].size() - 1; }
};

// 初期化
std::vector<rolling_hash::PowCache> RollingHash::pow_cache = {
    {1'000'000'007, 1007}, {1'000'000'009, 1009}};

} // namespace string
} // namespace zoi
