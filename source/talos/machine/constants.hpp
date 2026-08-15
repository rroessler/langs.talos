#ifndef _TALOS_MACHINE_CONSTANTS_HPP
#define _TALOS_MACHINE_CONSTANTS_HPP

/// Talos Includes
#include "talos/forward/machine.hpp"
#include "talos/value/void.hpp"

namespace Talos::Machine::Constants {

static inline constexpr Value::Any Void = Value::Void();
static inline constexpr Value::Any Fail = Value::Failure();

} // namespace Talos::Machine::Constants

#endif
