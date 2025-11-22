#pragma once

#include "std.hpp"

struct IOSetup{
  IOSetup(){
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout << fixed << setprecision(16);
  }
} io_setup;

template <typename T>
struct is_string
{
    static const bool value = false;
};

template <class T, class Traits, class Alloc>
struct is_string<std::basic_string<T, Traits, Alloc>>
{
    static const bool value = true;
};

template <typename F, typename S>
istream& operator>>(istream& is, pair<F, S>& p) {
  return is >> p.first >> p.second;
}

template <typename C>
requires requires(C container) {
begin(container);
end(container);
next(begin(container));
} && (!is_string<C>::value)
istream& operator>>(istream& is, C& container) {
  for(auto&& x : container) {
    is >> x;
  }
  return is;
}

