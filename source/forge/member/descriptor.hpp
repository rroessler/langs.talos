#ifndef _FORGE_MEMBER_DESCRIPTOR_HPP
#define _FORGE_MEMBER_DESCRIPTOR_HPP

/// Forge Modules
#include "forge/forward/member.hpp"
#include "forge/forward/runtime.hpp"
#include "forge/forward/value.hpp"

namespace Forge::Member {

    /// @brief Any Valid Descriptor.
    using View = Descriptor*;

    /// @brief The baseline descriptor.
    class $_ABSTRACT Descriptor {
        //  PROPERTIES  //

        /// @brief Denotes internal mutability.
        bool m_readonly = false;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a baseline descriptor.
        explicit Descriptor() = default;

        /**
         * @brief Constructs a descriptor.
         * @param readonly          Readonly flag.
         */
        explicit Descriptor(bool readonly) : m_readonly(readonly) {}

        /// @brief Virtual abstract destructor.
        virtual ~Descriptor() = default;

        //  PUBLIC METHODS  //

        /// @brief Gets the current readonly state.
        inline constexpr bool readonly() const noexcept { return m_readonly; }

        /**
         * @brief Handles getting the value.
         * @param isolate           Runtime isolate.
         * @param self              Self value.
         */
        virtual Value::Any getter(Runtime::Isolate* isolate, Value::Any self) const = 0;

        /**
         * @brief Handles setting the value.
         * @param isolate           Runtime isolate.
         * @param self              Self value.
         * @param value             Value to assign.
         */
        virtual Value::Any setter(Runtime::Isolate* isolate, Value::Any self, Value::Any value) = 0;
    };

}  // namespace Forge::Member

#endif
