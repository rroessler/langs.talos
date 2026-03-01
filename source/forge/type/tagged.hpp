#ifndef _FORGE_TYPE_UNIT_HPP
#define _FORGE_TYPE_UNIT_HPP

/// Forge Modules
#include "forge/operator/traits.hpp"
#include "forge/type/lattice.hpp"
#include "forge/value/common.hpp"

namespace Forge::Type {

    /// @brief Available Scalar Types.
    template <std::derived_from<Value::Any> T>
    class Scalar;

    /// @brief Encapsulates any type-units.
    struct $_ABSTRACT Tagged : public $::Printable, public $::Ptr::Castable<Tagged> {
        //  TYPEDEFS  //

        /// @brief Allow generics internal access.
        friend class Generic;

        /// @brief Allow transforms internal access.
        friend class Transform;

        //  CONSTRUCTORS  //

        /// @brief Virtual abstract destructor.
        virtual ~Tagged() = default;

        //  PUBLIC METHODS  //

        /// @brief The underlying type-lattice.
        virtual inline Lattice lattice() const noexcept { return Fact::ANY_TYPE; }

        /// @brief Gets a nodes associated truthiness.
        virtual inline $::Ternary truthiness() const noexcept { return $::Unknown(); }

        /// @brief Checks if a type is valid.
        template <class... As>
        inline constexpr bool is() const noexcept {
            return ((m_is<As>()) || ...);
        }

        /// @brief Handles casting to another type reference.
        template <std::derived_from<Tagged> T>
        inline constexpr $::Ptr::Shared<T> as() noexcept {
            return m_assert<T>(), m_as<T>();
        }

        /**
         * @brief Handles looking up a field on a type.
         * @param field                 Field to get.
         * @param globals               Global types.
         */
        virtual Entity lookup(const $::String::View& field) const;

        /**
         * @brief Applies a unary operator to the type.
         * @param kind                  Unary operator kind.
         */
        virtual Erased apply(Operator::Kind kind) const;
        inline constexpr Erased apply(const $::String::View& symbol) const {
            return apply(Operator::Traits::from(symbol));
        }

        /**
         * @brief Applies a binary operator to the type.
         * @param kind                  Binary operator kind.
         * @param right                 RHS type to apply to.
         */
        virtual Erased apply(Operator::Kind kind, const Erased& right) const;
        inline constexpr Erased apply(const $::String::View& symbol, const Erased& right) const {
            return apply(Operator::Traits::from(symbol), right);
        }

        /**
         * @brief Handles inferring generics.
         * @param constraints           Generic constraints.
         */
        inline constexpr Erased infer(const Constraints& constraints = nullptr) { return m_infer(constraints); }

        /**
         * @brief Checks if candidate is a subtype of this type.
         * @param candidate             Candidate to compare.
         * @param constraints           Generic constraints.
         */
        bool unify(const Erased& candidate, const Constraints& constraints = nullptr) const;

       protected:
        //  PROTECTED METHODS  //

        /**
         * @brief Handles checking types at runtime.
         * @param tag                   Tag to validate.
         */
        virtual bool m_is($::RTTI::Tag tag) const noexcept = 0;

        /// @brief Handles dispatching type-validation.
        template <class T>
        inline constexpr bool m_is() const noexcept {
            if constexpr (std::derived_from<T, Tagged>) return m_is($::RTTI::Hash<T>());
            else if constexpr (std::derived_from<T, Value::Any>) return m_extends(Shape::Lookup<T>());
            else static_assert(false, "T is not a supported type to validate");
        }

        /// @brief Handles cloning type-units.
        virtual Erased m_clone() const noexcept = 0;

        /// @brief The underlying tag value.
        virtual $::RTTI::Tag m_tag() const noexcept = 0;

        /**
         * @brief Handles type-instantiation.
         * @param constraints           Generic constraints.
         */
        virtual Erased m_infer(const Constraints&) const { return m_clone(); }

        /**
         * @brief Allows checking for value inheritance.
         * @param shape                 Shape to validate.
         */
        virtual bool m_extends(Shape::Underlying) const noexcept { return false; }

        /**
         * @brief Checks if candidate is a subtype of this type.
         * @param candidate             Candidate to compare.
         * @param constraints           Generic constraints.
         */
        virtual bool m_unify(const Erased& candidate, const Constraints& constraints) const = 0;

        /// @brief Handles asserting types.
        template <std::derived_from<Tagged> T>
        inline constexpr void m_assert() const {
            if constexpr (std::same_as<T, Tagged>) return;  // ignorable value here
            $_ASSERT(is<T>(), "Type does not extend '{0}'", $::RTTI::Name::of<T>());
        }

        /**
         * @brief Handles printing type-units.
         * @param os                    Output stream.
         */
        virtual void m_print($::Stream::Output& os) const = 0;

        /**
         * @brief Handles printing type-units.
         * @param os                    Output stream.
         * @param self                  Type instance.
         */
        static void m_print($::Stream::Output& os, const Tagged& self);

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles forwarding parameterized/generic inferrence.
        bool m_unify(const $::Ptr::Shared<Generic>& generic, const Constraints& constraints) const;
        bool m_unify(const $::Ptr::Shared<Parameter>& parameter, const Constraints& constraints) const;
    };

    /// Allows inheriting from abstract types.
    template <typename T, std::derived_from<Tagged> B = Tagged>
    struct $_ABSTRACT Abstract : public B {
        //  PROPERTIES  //

        /// @brief Inherit the base constructor.
        using B::B;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles cloning to the inherited class implementation.
        virtual inline Erased m_clone() const noexcept override { return $::New().shared<T>(*Tagged::m_as<T>()); }

        /// @brief Gets the underlying tag available.
        virtual inline $::RTTI::Tag m_tag() const noexcept override { return $::RTTI::Hash<T>(); }

        /**
         * @brief Handles checking for associated types.
         * @param tag                   Tag to compare.
         */
        virtual inline constexpr bool m_is($::RTTI::Tag tag) const noexcept override {
            static constexpr auto s_tag = $::RTTI::Hash<T>();  // hash
            if constexpr (std::same_as<B, Tagged>) return tag == s_tag;
            else return tag == s_tag || B::m_is(tag);  // check parent
        }
    };

}  // namespace Forge::Type

#endif
