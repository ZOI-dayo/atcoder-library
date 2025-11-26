//@yosupo division_of_big_integers

#include "../../../all.hpp"

void solve() {
  bint a, b;
  cin >> a >> b;
  bint x = a / b, y = a - x * b;
  cout << x << ' ' << y << '\n';
}

int main() {
  int t;
  cin >> t;
  while(t--) {
    solve();
  }
}