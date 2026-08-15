#ifndef _XTDLIB_CONTAINER_RANGES_HPP
#define _XTDLIB_CONTAINER_RANGES_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Ranges {

//  TYPEDEFS  //

/// @brief Available enumerator instance.
inline constexpr struct : std::ranges::range_adaptor_closure<class Each> {
  template <std::ranges::viewable_range R> inline constexpr auto operator()(R &&range) const {
    if constexpr (std::ranges::sized_range<R>) {
      auto distance = static_cast<size_t>(std::ranges::distance(range));
      return std::views::zip(std::views::iota(0UZ, distance), (R &&)range);
    } else return std::views::zip(std::views::iota(0UZ), (R &&)range);
  }
} Each;

/// @brief Available derefence view.
inline constexpr struct : std::ranges::range_adaptor_closure<class Deref> {
  template <std::ranges::viewable_range R> inline constexpr auto operator()(R &&range) const {
    return range | std::views::transform([](const auto &value) -> const auto & { return *value; });
  }
} Deref;

/// @brief Available container filter.
inline constexpr struct : std::ranges::range_adaptor_closure<class Filter> {
  //  OPERATOR METHODS  //

  template <std::ranges::viewable_range R, class P> inline constexpr auto operator()(R &&range, P &&predicate) const {
    return range | std::views::filter(predicate);
  }

  template <std::ranges::viewable_range R> inline constexpr auto operator()(R &&range) const {
    static_assert(std::is_pointer_v<std::ranges::range_value_t<R>>); // check
    return operator()(range, [](const auto &item) { return item != nullptr; });
  }

  //  PUBLIC METHODS  //

  template <std::ranges::viewable_range R, class P>
  inline constexpr std::ranges::range_value_t<R> first(R &&range, P &&predicate) const {
    static_assert(std::is_pointer<std::ranges::range_value_t<R>>());

    // attempt scanning for the item now
    for (const auto &item : range) {
      if (predicate(item)) return item;
    }

    // otherwise result as not found
    return nullptr;
  }
} Filter;

//  PUBLIC METHODS  //

/// @brief Casts a range to a vector.
template <std::ranges::viewable_range R>
static inline constexpr std::vector<std::ranges::range_value_t<R>> To(R &&range) {
  return std::vector(range.begin(), range.end());
}

/// @brief Casts a range to a typed vector.
template <class T, std::ranges::viewable_range R> static inline constexpr std::vector<T> To(R &&range) {
  static_assert(std::convertible_to<std::ranges::range_value_t<R>, T>);
  return std::vector<T>(range.begin(), range.end()); // can cast safely
}

/// @brief Replaces a vector with the given values.
template <class T, std::ranges::viewable_range R>
static inline constexpr std::vector<T> &Assign(std::vector<T> &target, R &&input) {
  return target.assign(input.begin(), input.end()), target;
}

/// @brief Appends an input range to a vector.
template <class T, std::ranges::viewable_range U>
static inline constexpr std::vector<T> &Append(std::vector<T> &target, U &&input) {
  target.reserve(target.size() + input.size()); // reserve total size
  return target.insert(target.end(), input.begin(), input.end()), target;
}

/// @brief Prepends an input range to a vector.
template <class T, std::ranges::viewable_range U>
static inline constexpr std::vector<T> &Prepend(std::vector<T> &target, U &&input) {
  target.reserve(target.size() + input.size()); // reserve total size
  return target.insert(target.begin(), input.begin(), input.end()), target;
}

} // namespace $::Ranges

#endif
