#ifndef _TALOS_REFLECT_INSPECT_HPP
#define _TALOS_REFLECT_INSPECT_HPP

/// Talos Includes
#include "talos/reflect/category.hpp"

namespace Talos::Reflect::Inspect {

/**
 * @brief Handles resolving feature labels.
 * @param value                 Value to convert.
 */
static inline constexpr $::String::View feature(Feature value) {
#define X(F, N, ...)         \
  case Feature::F: return N;
  switch (value) { TALOS_XX_REFLECTION_FEATURES(X) default : return "Invalid"; }
#undef X
}

/**
 * @brief Handles resolving feature values.
 * @param text                  Text to parse.
 */
static inline constexpr Feature feature(const $::String::View &text) {
#define X(F, N, ...)                       \
  case XH::FNV::U32(N): return Feature::F;
  switch (XH::FNV::U32(text)) { TALOS_XX_REFLECTION_FEATURES(X) default : return Feature::INVALID; }
#undef X
}

/**
 * @brief Handles resolving category names.
 * @param value                 Value to convert.
 */
static inline constexpr $::String::View category(Category value) {
#define X(C, N, L, ...)       \
  case Category::C: return L;
  switch (value) { TALOS_XX_REFLECTION_CATEGORIES(X) default : return "Invalid"; }
#undef X
}

/**
 * @brief Handles resolving category values.
 * @param text                  Text to parse.
 */
static inline constexpr Category category(const $::String::View &text) {
#define X(C, N, L, ...)                     \
  case XH::FNV::U32(L): return Category::C;
  switch (XH::FNV::U32(text)) { TALOS_XX_REFLECTION_CATEGORIES(X) default : return Category::INVALID; }
#undef X
}

} // namespace Talos::Reflect::Inspect

#endif
