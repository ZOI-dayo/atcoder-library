//@yosupo addition_of_big_integers

#include "../../../all.hpp"

void solve() {
  bint a, b;
  fin >> a >> b;
  fout << a + b << '\n';
}

int main() {
  int t;
  fin >> t;
  while(t--) {
    solve();
  }
}