#ifndef _FORGE_OBJECT_ABSTRACT_HPP
#define _FORGE_OBJECT_ABSTRACT_HPP

/// Forge Includes
#include "forge/object/common.hpp"
#include "forge/object/guard.hpp"
#include "forge/value/void.hpp"

namespace Forge::Object {

    /// @brief Allocatable Object Attributes.
    template <class T>
    struct Attributes;

    /// @brief Object Abstraction CRPT.
    template <class T>
    struct Abstract : public Value::Any {
        //  TYPEDEFS  //

        /// @brief Ensure that the attributes allocation will fit.
        static_assert(sizeof(Attributes<T>) <= UINT8_MAX);

        //  CONSTRUCTORS  //

        /**
         * @brief Consturcts a tagged object.
         * @param pointer                   Optional pointer.
         */
        constexpr Abstract() : Value::Any(Object::Any()) {}
        constexpr Abstract(Pointer::Underlying pointer) : Value::Any(pointer) {
            $_ASSERT(m_is(m_pointer), "Invalid '{0}' address 0x{1:08X}", $::RTTI::Name::of<T>(), m_pointer);
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Constructs a suitable value guard.
        inline constexpr Guard m_guard() const noexcept { return Guard(*this); }

        /// @brief Gets the object address.
        inline constexpr Pointer::Underlying m_address() const noexcept { return m_as<Object::Any>().address(); }

        /// @brief Gets the underlying attributes.
        inline constexpr Attributes<T> *m_attrs() const noexcept { return std::bit_cast<Attributes<T> *>(m_address()); }

        /**
         * @brief Validates incoming pointers.
         * @param pointer                   Pointer to validate.
         */
        static inline constexpr bool m_is(const Pointer::Traits &traits) {
            if (traits.kind() < Pointer::Kind::OBJ) return false;
            return Object::Any(traits).header()->is<T>();
        }

        /**
         * @brief Forces calls for truthiness to query base.
         * @param self                      Value to resolve.
         */
        static inline constexpr bool m_truthiness(const Any &self) { return self.truthiness(); }

        /**
         * @brief Handles printing generic values.
         * @param os                        Output stream.
         * @param self                      Object value.
         */
        static inline void m_print($::Stream::Output &os, const T &self) {
            os << $::Dye::cyan("<{0}: 0x{1:08X}>", self.type_name(), self.m_pointer);
        }
    };

}  // namespace Forge::Object

#endif
