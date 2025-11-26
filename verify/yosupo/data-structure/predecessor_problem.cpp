//@yosupo predecessor_problem

#include "../../../all.hpp"

void solve()
{
  int n, q, c, k;
  string t;
  cin >> n >> q >> t;
  FastSet fs(t);
  while (q--)
  {
    cin >> c >> k;
    if (c == 0)
    {
      fs.insert(k);
    }
    else if (c == 1)
    {
      fs.erase(k);
    }
    else if (c == 2)
    {
      cout << fs.contains(k) << '\n';
    }
    else if (c == 3)
    {
      cout << fs.next(k, -1) << '\n';
    }
    else if (c == 4)
    {
      cout << fs.prev(k, -1) << '\n';
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