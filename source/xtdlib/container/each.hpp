#ifndef _XTDLIB_CONTAINER_EACH_HPP
#define _XTDLIB_CONTAINER_EACH_HPP

/// C++ Modules
#include <ranges>

namespace $ {

    /// @brief Available enumerator instance.
    inline constexpr struct : std::ranges::range_adaptor_closure<class Each> {
        template <std::ranges::viewable_range R>
        inline constexpr auto operator()(R&& range) const {
            if constexpr (std::ranges::sized_range<R>) {
                auto distance = static_cast<size_t>(std::ranges::distance(range));
                return std::views::zip(std::views::iota(0UZ, distance), (R&&)range);
            } else return std::views::zip(std::views::iota(0UZ), (R&&)range);
        }
    } Each;

}  // namespace $

#endif
