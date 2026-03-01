#ifndef _FORGE_FLOW_UNREACHABLE_HPP
#define _FORGE_FLOW_UNREACHABLE_HPP

/// Type Modules
#include "forge/flow/control.hpp"

namespace Forge::Flow {

    /// @brief Unreachable Control Flow.
    class Unreachable : public Abstract<Unreachable> {
        //  PROPERTIES  //

        /// @brief Associated control effect.
        Effect m_effect;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an unreachable control flow.
         * @param degree                Unreachable degree.
         * @param effect                Optional side-effect.
         */
        explicit constexpr Unreachable(Degree degree, Effect effect = Effect::NONE) :
            Abstract<Unreachable>(degree), m_effect(effect) {
            $_ASSERT(unreachable(), "Expected a non-negative reachability value");
        }

        //  PUBLIC METHODS  //

        /// @brief Gets the associated side-effect.
        inline Effect effect() const noexcept final { return m_effect; }
    };

}  // namespace Forge::Flow

#endif
