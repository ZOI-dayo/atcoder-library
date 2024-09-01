#include <ranges>
#include <vector>

namespace zoi {
namespace view {

struct to_vec_adoptor {
  friend constexpr auto operator|(std::ranges::viewable_range auto &&r,
                                  to_vec_adoptor self) {
    auto r_common = r | std::views::common;
    return std::vector(r_common.begin(), r_common.end());
  }
};
inline constexpr to_vec_adoptor to_vec;

}
}
