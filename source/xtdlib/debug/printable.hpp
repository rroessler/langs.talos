#ifndef _XTDLIB_DEBUG_PRINTABLE_HPP
#define _XTDLIB_DEBUG_PRINTABLE_HPP

/// Library Includes
#include "xtdlib/color/facet.hpp"
#include "xtdlib/macros/attributes.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"
#include "xtdlib/utility/static.hpp"
#include "xtdlib/vendors/fmt.hpp"

namespace $::Printable {

/// @brief Printable Inspection.
template <class T> class Inspect : protected T {
  //  TYPEDEFS  //

  /// @brief Allow the enablement handler.
  template <class> friend constexpr bool Enabled();

public:
  //  PUBLIC METHODS  //

  /**
   * @brief Handles coordinating printing values.
   * @param os                      Output stream.
   * @param self                    Item to print.
   */
  static $_INLINE_ALWAYS constexpr void print(std::ostream &os, const T &self) { T::m_print(os, self); }

  /**
   * @brief Handles coordinating stringifying values.
   * @param self                    Item to print.
   */
  static $_INLINE_ALWAYS constexpr String::Buffer strip(const T &self) {
    auto oss = std::stringstream(); // oss
    return T::m_print(oss, self), oss.str();
  }

private:
  //  PRIVATE METHODS  //

  /// @brief Denotes an encoder validation.
  static inline constexpr bool m_enabled() {
    return requires(std::ostream &os, const T &self) {
      { T::m_print(os, self) } -> std::same_as<void>;
    };
  }
};

/// @brief Denotes if an item is printable.
template <class T> static inline constexpr bool Enabled() {
  if constexpr (!std::is_class_v<T>) return false;
  else return Inspect<T>::m_enabled(); // resolve
}

} // namespace $::Printable

//  SPECIALIZATIONS  //

namespace std {

/**
 * @brief Enables printing any value from "std::ostream" operators.
 * @param os                      Output stream.
 * @param self                    Item to print.
 */
template <class T>
  requires($::Printable::Enabled<T>())
static $_INLINE_ALWAYS std::ostream &operator<<(std::ostream &os, const T &value) {
  return $::Printable::Inspect<T>::print(os, value), os;
}

} // namespace std

template <class T>
struct fmt::formatter<T, std::enable_if_t<$::Printable::Enabled<T>(), char>> : fmt::formatter<$::String::View, char> {
  //  PUBLIC METHODS  //

  /**
   * @brief Handles formatting printable values.
   * @param value                   Value to format.
   * @param ctx                     Format context.
   */
  inline constexpr auto format(const T &value, fmt::format_context &ctx) const -> decltype(ctx.out()) {
    // prepare a memory buffer for "fmtlib" to use
    auto memory = fmt::basic_memory_buffer<char>();
    auto &&buffer = fmt::detail::formatbuf<std::basic_streambuf<char>>(memory);
    auto &&os = std::basic_ostream<char>(&buffer);

#ifndef FMT_STATIC_THOUSANDS_SEPARATOR
    // ensure the correct locale being used
    os.imbue(std::locale::classic());
#endif

    // determine if we are using colors or not
    const auto pretty = m_pretty(ctx);

    // actually print the output now
    if (pretty) $::Color::Enabled(os, true);
    $::Printable::Inspect<T>::print(os, value);
    if (pretty) $::Color::Enabled(os, false);

    // ignore exceptions produced (unsure why)
    os.exceptions(std::ios_base::failbit | std::ios_base::badbit);

    // prepare the resulting output text to be formatted
    $::String::View view = {memory.data(), memory.size()};
    return fmt::formatter<$::String::View, char>::format(view, ctx);
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Checks if the context is prettified.
   * @param ctx                   Context to query.
   */
  inline constexpr bool m_pretty(fmt::format_context &ctx) const {
    auto locale = ctx.locale().get<std::locale>();
    if (!std::has_facet<$::Color::Facet>(locale)) return false;
    return std::use_facet<$::Color::Facet>(locale).enabled;
  }
};

#endif
