#pragma once

#include "std.hpp"

void io_setup() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  cout << fixed << setprecision(16);
}

template <typename C>
requires requires(C container) {
begin(container);
end(container);
next(begin(container));
}
istream& operator>>(istream& is, C& container) {
  for(auto&& x : container) {
    is >> x;
  }
  return is;
}

template <typename F, typename S>
istream& operator>>(istream& is, pair<F, S>& p) {
  return is >> p.first >> p.second;
}
