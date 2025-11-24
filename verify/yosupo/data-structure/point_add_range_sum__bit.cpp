//@yosupo point_add_range_sum

#include "../../../all.hpp"

void solve()
{
  int n, q;
  fin >> n >> q;
  vl a(n);
  fin >> a;
  BIT<>
      bit(a);
  while (q--)
  {
    bool t;
    fin >> t;
    if (!t)
    {
      ll p, x;
      fin >> p >> x;
      bit.apply(p, x);
    }
    else
    {
      int l, r;
      fin >> l >> r;
      fout << bit.prod(l, r) << '\n';
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