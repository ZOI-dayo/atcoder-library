//@yosupo point_add_range_sum

#include "../../../all.hpp"

void solve()
{
  int n, q;
  cin >> n >> q;
  vl a(n);
  cin >> a;
  SegmentTree<
      ll,
      0,
      [](ll a, ll b)
      { return a + b; }>
      seg(a);
  while (q--)
  {
    bool t;
    cin >> t;
    if (!t)
    {
      ll p, x;
      cin >> p >> x;
      seg[p] = seg[p] + x;
    }
    else
    {
      ll l, r;
      cin >> l >> r;
      cout << seg[l, r] << '\n';
    }
  }
}

int main()
{
  int t = 1;
  //   cin >> t;
  while (t--)
  {
    solve();
  }
}