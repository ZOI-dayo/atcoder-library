#include <iomanip>
#include <iostream>

inline void io_setup() {
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
}

#include "../all.hpp"

using namespace zoi;
using namespace zoi::geometry;
using namespace zoi::datastructure;
using namespace zoi::math;
using namespace zoi::graph;
using namespace zoi::util;
using namespace zoi::int128;
// using namespace zoi::string;
using namespace zoi::concepts;

using namespace std;

using ll = long long;

template <typename T> using vec = vector<T>;
template <typename T> using vvec = vec<vec<T>>;

#define rep(i, n) for (ll i = 0; i < n; ++i)
