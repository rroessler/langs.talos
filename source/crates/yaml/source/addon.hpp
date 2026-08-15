#ifndef _CRATES_ADDON_YAML_HPP
#define _CRATES_ADDON_YAML_HPP

/// Addon Includes
#include <talos/dylib/_inline/dylib.ipp>

//  X-MACROS  //

#define CRATE_XX_YAML_METHODS(X) \
  X(encode)                      \
  X(decode)

//  NAMESPACES  //

namespace Talos::Package {

/// @brief YAML Package Addon.
struct YAML : public Dylib::Mixin<"yaml"> {
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a "yaml" library.
   * @param isolate               Runtime isolate.
   * @param exports               Addon exports.
   */
  explicit YAML(Runtime::Isolate *isolate, Dylib::Exports &exports);

private:
  //  PRIVATE METHODS  //

  CRATE_XX_YAML_METHODS(TALOS_MM_DYLIB_DEFINE)
};

} // namespace Talos::Package

#endif
