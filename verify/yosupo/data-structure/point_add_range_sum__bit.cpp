//@yosupo point_add_range_sum

#include "../../../all.hpp"

void solve()
{
  int n, q;
  cin >> n >> q;
  vl a(n);
  cin >> a;
  BIT<>
      bit(a);
  while (q--)
  {
    bool t;
    cin >> t;
    if (!t)
    {
      ll p, x;
      cin >> p >> x;
      bit[p] += x;
    }
    else
    {
      int l, r;
      cin >> l >> r;
      fout << bit[l, r] << '\n';
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