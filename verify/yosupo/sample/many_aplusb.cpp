//@yosupo many_aplusb

#include "../../../all.hpp"

uint n;

inline void solve() {
  cin >> n;
  for(uint i=0; i<n; i++) {
    ull a, b;
    cin >> a >> b;
    cout << a + b << '\n';
  }
}

int main() {
  int t = 1;
  // cin >> t;
  while(t--) {
    solve();
  }
}