//@yosupo point_add_range_sum

#include "../../../all.hpp"

void solve()
{
  int n, q;
  fin >> n >> q;
  vl a(n);
  fin >> a;
  SegmentTree<
      ll,
      0,
      plus<ll>{}>
      seg(a);
  while (q--)
  {
    bool t;
    fin >> t;
    if (!t)
    {
      ll p, x;
      fin >> p >> x;
      seg[p] = seg[p] + x;
    }
    else
    {
      int l, r;
      fin >> l >> r;
      fout << seg[l, r] << '\n';
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