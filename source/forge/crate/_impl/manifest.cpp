/// Forge Includes
#include "forge/crate/manifest.hpp"

//  PRIVATE METHODS  //

std::optional<$::URI::Buffer> Forge::Crate::Manifest::m_resolve(
    const std::optional<$::String::Buffer>& relative) const {
    // ensure the incoming value is valid
    if (!relative.has_value()) return std::nullopt;

    // and ensure the absolute value is also valid
    auto absolute = $::Path::canonical(*relative, m_path);
    return $::URI::Buffer($::URI::Scheme::FILE, absolute.string());
}
