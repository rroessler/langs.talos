#ifndef _TALOS_ANNOTATION_GENERIC_HPP
#define _TALOS_ANNOTATION_GENERIC_HPP

/// Syntax Includes
#include "talos/syntax/annotation/placeholder.hpp"

namespace Talos::Syntax {

/// @brief Generic Parameters Container.
using Template = std::vector<Placeholder *>;

/// @brief Generic Arguments Container.
using Specialization = std::vector<Annotation *>;

} // namespace Talos::Syntax

#endif
