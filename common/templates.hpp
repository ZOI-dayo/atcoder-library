#include <iomanip>
#include <iostream>

inline void io_setup() {
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
}
