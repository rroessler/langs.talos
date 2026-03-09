#ifndef _TALOS_RESOURCE_PATH_HPP
#define _TALOS_RESOURCE_PATH_HPP

/// Talos Includes
#include "talos/resource/scheme.hpp"

/// Forward Declarations
$_FWD(Talos::Resource, using Result = std::expected<$::URI::Buffer, $::String::Buffer>)

namespace Talos::Resource::Path {

    //  PUBLIC METHODS  //

    /**
     * @brief Attempts resolving a resource path.
     * @param resource                          Resource value.
     * @param hint                              Hint to use.
     */
    Result resolve(const $::URI::View& resource, const $::Filesystem::Path& hint = $::System::cwd());

    /**
     * @brief Attempts resolving a resource path.
     * @param script                            Script path.
     * @param hint                              Hint to use.
     */
    Result resolve(const $::String::View& script, const $::Filesystem::Path& hint = $::System::cwd());

    /**
     * @brief Attempts resolving a resource path.
     * @tparam S                                Scheme to use.
     * @param body                              Resource body.
     * @param hint                              Hint to use.
     */
    template <Scheme S>
    Result resolve(const $::String::View& body, const $::Filesystem::Path& hint = $::System::cwd());

    //  SPECIALIZATIONS  //

#define X(N, ...) \
    template <>   \
    Result resolve<Scheme::N>(const $::String::View&, const $::Filesystem::Path&);
    TALOS_XX_RESOURCE_SCHEMES(X)
#undef X

}  // namespace Talos::Resource::Path

#endif
