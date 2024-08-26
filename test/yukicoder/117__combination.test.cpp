#define PROBLEM "https://yukicoder.me/problems/no/117"

#include "../../common/template.hpp"
#include "../../math/combination.hpp"

signed main() {
  io_setup();
  int T;
  cin >> T;
  using Cmb = Combination<1'000'000'007, 2000010>;
  rep(i, T) {
    string S;
    cin >> S;
    char mode;
    int32_t n, r;
    sscanf(S.c_str(), "%c(%d,%d)", &mode, &n, &r);
    if (mode == 'C') {
      cout << Cmb::nCr(n, r) << endl;
    } else if (mode == 'P') {
      cout << Cmb::nPr(n, r) << endl;
    } else if (mode == 'H') {
      cout << Cmb::nHr(n, r) << endl;
    }
  }
}
