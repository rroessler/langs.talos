#ifndef _TALOS_OBJECT_CLASS_HPP
#define _TALOS_OBJECT_CLASS_HPP

/// Talos Modules
#include "talos/member/reference.hpp"
#include "talos/object/abstract.hpp"
#include "talos/string/dynamic.hpp"

/// Forward Definitions
$_FWD(Talos::Object, using Fields = $::Map<Value::Symbol, $::Ptr::Unique<Member::Reference>>)

namespace Talos {

    /// @brief Class Attributes.
    template <>
    struct Object::Attributes<Object::Class> {
        //  PROPERTIES  //

        Fields statics;           // Static fields.
        Value::Any parent;        // Ancestor value.
        String::Dynamic name;     // Exposed class name.
        Shape::Underlying shape;  // Bound shape value.

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a class prototype.
         * @param name                  Name of class.
         * @param shape                 Shape of class.
         * @param parent                Ancestor class.
         */
        explicit Attributes(String::Dynamic name, Shape::Underlying shape, Value::Any parent = Value::Void()) :
            parent(parent), name(name), shape(shape) {}

        /**
         * @brief Constructs a class prototype.
         * @param isolate               Runtime isolate.
         * @param name                  Name of class.
         * @param parent                Ancestor class.
         */
        explicit Attributes(Runtime::Isolate* isolate, const $::String::View& name, Shape::Underlying shape,
            Value::Any parent = Value::Void()) :
            Attributes(String::Dynamic(isolate, name), shape, parent) {}
    };

    /// @brief Class Interface.
    struct Object::Class : public Object::Abstract<Object::Class> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  /

        inline constexpr Fields& statics() const noexcept { return m_attrs()->statics; }
        inline constexpr Value::Any& parent() const noexcept { return m_attrs()->parent; }
        inline constexpr String::Dynamic& name() const noexcept { return m_attrs()->name; }

        /**
         * @brief Checks if a value extends this class.
         * @param value                 Value to check.
         */
        inline constexpr bool extends(Value::Any value) const noexcept { return extends(value.shape()); }
        inline constexpr bool extends(Shape::Underlying shape) const noexcept {
            if (m_attrs()->shape == shape) return true;
            auto parent = m_attrs()->parent;  // parent
            if (!parent.is<Object::Class>()) return false;
            return parent.as<Object::Class>().extends(shape);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handlers yielding classes safely.
         * @param self                          Class instance.
         * @param yield                         Yield callback.
         */
        static void m_yield(const Class& self, const Globals::Each& yield);

        /**
         * @brief Handles printing values.
         * @param os                    Output stream.
         * @param self                  Class instance.
         */
        static inline void m_print($::Stream::Output& os, const Class& self) {
            os << $::Dye::cyan("<{0}: {1}>", self.type_name(), self.name());
        }
    };

}  // namespace Talos

#endif
