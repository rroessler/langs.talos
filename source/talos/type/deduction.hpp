#ifndef _TALOS_TYPE_DEDUCTION_HPP
#define _TALOS_TYPE_DEDUCTION_HPP

/// Talos Modules
#include "talos/flow/passable.hpp"
#include "talos/forward/type.hpp"

namespace Talos::Type {

    /// @brief Type Deduction Result.
    struct Deduction {
        //  PROPERTIES  //

        /// @brief Resultant type.
        Erased type;

        /// @brief Flow control node.
        $::Ptr::Unique<Flow::Control> flow;

        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        constexpr Deduction() = delete;

        /**
         * @brief Constructs a passable deduction.
         * @param type                  Type to pass.
         */
        constexpr Deduction(const Erased& type) : type(type), flow($::New().unique<Flow::Passable>()) {}

        /**
         * @brief Constructs a passable deduction.
         * @param type                  Type to pass.
         * @param flow                  Flow to pass.
         */
        explicit constexpr Deduction(const Erased& type, $::Ptr::Unique<Flow::Control>&& flow) :
            type(type), flow(std::move(flow)) {}
    };

}  // namespace Talos::Type

#endif
