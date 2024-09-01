#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/4/DSL_4_A"

#include "../../common/template.hpp"
#include "../../2d/point.hpp"
#include "../../datastructure/comp.hpp"
#include "../../datastructure/imos2d.hpp"

signed main() {
  io_setup();
  int N;
  cin >> N;
  vec<int> xs(2 * N), ys(2 * N);
  rep(i, N) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    xs[2 * i] = x1;
    ys[2 * i] = y1;
    xs[2 * i + 1] = x2;
    ys[2 * i + 1] = y2;
  }
  comp<int> cx(xs), cy(ys);
  imos2d<int> imos(cx.cmp_size(), cy.cmp_size());
  rep(i, N) {
    Point a(cx[2 * i], cy[2 * i]), b(cx[2 * i + 1], cy[2 * i + 1]);
    imos.add(a, b, 1);
  }
  imos.build();
  int ans = 0;
  rep(x, cx.cmp_size() - 1) rep(y, cy.cmp_size() - 1) {
    ans += (imos.get(Point(x, y)) > 0) * (cx.get_raw(x + 1) - cx.get_raw(x)) *
           (cy.get_raw(y + 1) - cy.get_raw(y));
  }
  cout << ans << endl;
}
