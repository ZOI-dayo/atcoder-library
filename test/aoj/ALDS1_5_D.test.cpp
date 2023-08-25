#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/5/ALDS1_5_D"

#include "../../datastructure/bit/bit.hpp"

// 転倒数
int main() {
  int n;
  cin >> n;
  vec<int> a(n);
  rep(i, n) cin >> a[i];
  auto a_copy = a;
  sort(all(a_copy));
  rep(i, n) a[i] = lower_bound(all(a_copy), a[i]) - a_copy.begin();
  BIT<ll> bit(n);
  ll ans = 0;
  rep(i, n) {
    ans += i - bit.sum(a[i]);
    bit.add(a[i], 1);
  }
  cout << ans << endl;
}
