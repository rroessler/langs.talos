#ifndef _CRATES_PACKAGE_JSON_HPP
#define _CRATES_PACKAGE_JSON_HPP

/// Addon Includes
#include <talos/dylib/_inline/dylib.ipp>

//  X-MACROS  //

#define CRATE_XX_JSON_METHODS(X) \
  X(encode)                      \
  X(decode)

//  NAMESPACES  //

namespace Talos::Package {

/// @brief JSON Package Addon.
struct JSON : public Dylib::Mixin<"json"> {
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a "json" library.
   * @param isolate               Runtime isolate.
   * @param exports               Addon exports.
   */
  explicit JSON(Runtime::Isolate *isolate, Dylib::Exports &exports);

private:
  //  PRIVATE METHODS  //

  CRATE_XX_JSON_METHODS(TALOS_MM_DYLIB_DEFINE)
};

} // namespace Talos::Package

#endif
