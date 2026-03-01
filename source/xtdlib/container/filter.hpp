#ifndef _XTDLIB_CONTAINER_FILTER_HPP
#define _XTDLIB_CONTAINER_FILTER_HPP

/// C++ Modules
#include <ranges>

namespace $ {

    /// @brief Available container filter.
    inline constexpr struct : std::ranges::range_adaptor_closure<class Filter> {
        //  OPERATOR METHODS  //

        template <std::ranges::viewable_range R, class P>
        inline constexpr auto operator()(R&& range, P&& predicate) const {
            return range | std::views::filter(predicate);
        }

        template <std::ranges::viewable_range R>
        inline constexpr auto operator()(R&& range) const {
            static_assert(std::is_pointer_v<std::ranges::range_value_t<R>>);  // check
            return operator()(range, [](const auto& item) { return item != nullptr; });
        }

        //  PUBLIC METHODS  //

        template <std::ranges::viewable_range R, class P>
        inline constexpr std::ranges::range_value_t<R> first(R&& range, P&& predicate) const {
            static_assert(std::is_pointer<std::ranges::range_value_t<R>>());

            // attempt scanning for the item now
            for (const auto& item : range) {
                if (predicate(item)) return item;
            }

            // otherwise result as not found
            return nullptr;
        }
    } Filter;

}  // namespace $

#endif
