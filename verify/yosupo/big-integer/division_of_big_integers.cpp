//@yosupo division_of_big_integers

#include "../../../all.hpp"

void solve() {
  bint a, b;
  fin >> a >> b;
  bint x = a / b, y = a - x * b;
  fout << x << ' ' << y << '\n';
}

int main() {
  int t;
  fin >> t;
  while(t--) {
    solve();
  }
}