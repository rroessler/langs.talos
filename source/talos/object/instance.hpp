#ifndef _TALOS_OBJECT_INSTANCE_HPP
#define _TALOS_OBJECT_INSTANCE_HPP

/// Talos Modules
#include "talos/object/class.hpp"

namespace Talos {

    /// @brief Instance Attributes.
    template <>
    struct Object::Attributes<Object::Instance> {
        //  PROPERTIES  //

        /// @brief Bound prototype instance.
        Class prototype;

        /// @brief Bound instance fields.
        Fields fields = {};

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a defaulted object instance.
         * @param isolate               Runtime isolate.
         */
        explicit Attributes(Runtime::Isolate* isolate);

        /**
         * @brief Constructs a class instance.
         * @param isolate               Runtime isolate.
         * @param inherits              Class to inherit.
         */
        explicit Attributes(const Class& inherits) : prototype(inherits) {}
    };

    /// @brief Instance Interface.
    struct Object::Instance : public Object::Abstract<Object::Instance> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        inline constexpr Fields& fields() const noexcept { return m_attrs()->fields; }
        inline constexpr const Class& prototype() const noexcept { return m_attrs()->prototype; }
        inline constexpr const String::Dynamic& name() const noexcept { return prototype().name(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handlers yielding instances safely.
         * @param self                          Value instance.
         * @param yield                         Yield callback.
         */
        static void m_yield(const Instance& self, const Globals::Each& yield);

        /**
         * @brief Handles printing values.
         * @param os                    Output stream.
         * @param self                  Object instance.
         */
        static inline void m_print($::Stream::Output& os, const Instance& self) {
            os << $::Dye::cyan("<{0}: 0x{1:08X}>", self.name(), self.m_pointer);
        }
    };

}  // namespace Talos

#endif
