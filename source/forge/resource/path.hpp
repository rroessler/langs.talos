#ifndef _FORGE_RESOURCE_PATH_HPP
#define _FORGE_RESOURCE_PATH_HPP

/// Forge Includes
#include "forge/resource/scheme.hpp"

/// Forward Declarations
$_FWD(using Result = std::expected<$::URI::Buffer $_PP_COMMA $::String::Buffer>, Forge::Resource)

namespace Forge::Resource::Path {

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
    FORGE_XX_RESOURCE_SCHEMES(X)
#undef X

}  // namespace Forge::Resource::Path

#endif
