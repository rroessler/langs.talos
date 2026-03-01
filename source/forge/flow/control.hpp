#ifndef _FORGE_FLOW_CONTROL_HPP
#define _FORGE_FLOW_CONTROL_HPP

/// Type Modules
#include "forge/flow/effect.hpp"

namespace Forge::Flow {

    /// @brief Flow Reachability Degree Type.
    using Degree = int32_t;

    /// @brief Flow State.
    class $_ABSTRACT Control : public $::RTTI::Dynamic {
        //  PROPERTIES  //

        /// @brief Current reachability depth.
        Degree m_degree;

       public:
        //  CONSTRUCTORS  //

        /// @brief Remove the default constructor.
        explicit constexpr Control() = delete;

        /**
         * @brief Constructs a suitable state.
         * @param degree            Reachability degree.
         */
        explicit constexpr Control(Degree degree) : m_degree(degree) {}

        /// @brief Allow virtual destruction.
        virtual ~Control() = default;

        //  PUBLIC METHODS  //

        inline constexpr Degree degree() const noexcept { return m_degree; }
        inline constexpr bool passable() const noexcept { return m_degree < 0; }
        inline constexpr bool unreachable() const noexcept { return m_degree > -1; }
        virtual inline Effect effect() const noexcept { return Effect::NONE; }
    };

    /// @brief Control Inheritance Abstraction.
    template <class T>
    using Abstract = $::RTTI::Extends<T, Control>;

}  // namespace Forge::Flow

#endif
