#ifndef _FORGE_FUNCTION_ANY_HPP
#define _FORGE_FUNCTION_ANY_HPP

/// Forge Modules
#include "forge/function/closure.hpp"
#include "forge/function/jitted.hpp"
#include "forge/function/native.hpp"

namespace Forge::Function {

    /// @brief Any Function Pointer.
    struct Dynamic : public Value::Any {
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty object.
        constexpr Dynamic() : Any(Object::Any()) {}

        /**
         * @brief Constructs a dynamic function.
         * @param pointer           Pointer to function.
         */
        constexpr Dynamic(Pointer::Underlying pointer) : Any(pointer) { $_ASSERT(is<Dynamic>()); }

        /**
         * @brief Constructs a dynamic function.
         * @param underlying        Underlying function.
         */
        constexpr Dynamic(Native native) : Any(native) {}
        constexpr Dynamic(Jitted jitted) : Any(jitted) {}
        constexpr Dynamic(Closure closure) : Any(closure) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the minimum allowed arguments.
        inline constexpr uint64_t arity() const noexcept {
            return m_apply<uint64_t>(0, [](auto value) { return value.arity(); });
        }

        /// @brief Gets the maximum allowed arguments.
        inline constexpr uint64_t adicity() const noexcept {
            return m_apply<uint64_t>(UINT64_MAX, [](auto value) { return value.adicity(); });
        }

        /// @brief Gets the associated function resource.
        inline constexpr $::URI::View resource() const noexcept {
            return m_apply<$::URI::View>($::URI::Anonymous(), [](auto value) { return value.resource(); });
        }

        /// @brief Gets the associated receiver value.
        inline constexpr Value::Any receiver() const noexcept {
            return m_apply<Value::Any>(Value::Void(), [](auto value) { return value.receiver(); });
        }

        /// @brief Denotes if we have a nullptr object.
        inline constexpr bool nptr() const noexcept { return Object::Any(traits()).nptr(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles applying a string callback.
         * @param callback                      Callback to run.
         */
        template <class R, class F>
        inline constexpr R m_apply(const R& preset, F callback) const noexcept {
            // handle based on the incoming shape
            switch (shape()) {
                case Shape::Lookup<Native>(): return callback(m_as<Native>());
                case Shape::Lookup<Jitted>(): return callback(m_as<Jitted>());
                case Shape::Lookup<Closure>(): return callback(m_as<Closure>());

                // default to the base instance
                default: return preset;
            }
        }

        /**
         * @brief Checks for valid functions.
         * @param traits            Pointer traits.
         */
        static inline constexpr bool m_is(const Pointer::Traits& traits) {
            if (traits.kind() < Pointer::Kind::OBJ) return false;  // check
            return Object::Any(traits).header()->is<Native, Jitted, Closure>();
        }

        /**
         * @brief Handles printing values.
         * @param os                Output stream.
         * @param self              Dynamic function.
         */
        static inline void m_print($::Stream::Output& os, const Dynamic& self) { os << Object::Any(self.traits()); }
    };

}  // namespace Forge::Function

#endif
