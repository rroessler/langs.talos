#ifndef _FORGE_ANNOTATION_GENERIC_HPP
#define _FORGE_ANNOTATION_GENERIC_HPP

/// Syntax Includes
#include "forge/syntax/annotation/placeholder.hpp"

namespace Forge::Syntax {

    /// @brief Generic Parameters Container.
    using Template = std::vector<Placeholder*>;

    /// @brief Generic Arguments Container.
    using Specialization = std::vector<Annotation*>;

}  // namespace Forge::Syntax

#endif
