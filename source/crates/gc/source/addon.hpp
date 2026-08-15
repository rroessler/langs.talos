#ifndef _CRATES_PACKAGE_GARBAGE_HPP
#define _CRATES_PACKAGE_GARBAGE_HPP

/// Talos Includes
#include <talos/garbage/service.hpp>

/// Addon Includes
#include <talos/dylib/_inline/dylib.ipp>

//  X-MACROS  //

#define CRATE_XX_GARBAGE_METHODS(X) \
  X(cycles)                         \
  X(collect)

//  NAMESPACES  //

namespace Talos::Package {

/// @brief Garbage Package Addon.
class Garbage : public Dylib::Mixin<"gc"> {
  //  TYPEDEFS  //

  /// @brief Available service typing.
  using Service = ::Talos::Garbage::Service;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs an assertion library.
   * @param isolate               Runtime isolate.
   * @param exports               Addon exports.
   */
  explicit Garbage(Runtime::Isolate *isolate, Dylib::Exports &exports);

private:
  //  PRIVATE METHODS  //

  CRATE_XX_GARBAGE_METHODS(TALOS_MM_DYLIB_DEFINE)
};

} // namespace Talos::Package

#endif
