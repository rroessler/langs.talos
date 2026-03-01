#ifndef _XASM_HOSTED_CONSTANTS_HPP
#define _XASM_HOSTED_CONSTANTS_HPP

/// XASM Modules
#include "xasm/forward/hosted.hpp"

namespace XASM::Constants {

    //  PROPERTIES  //

    /// @brief The maximum allowed registers count.
    static constexpr auto REGISTERS = asmjit::Operand::kVirtIdCount;

}  // namespace XASM::Constants

#endif
