#ifndef _FORGE_TYPE_INTRINSICS_HPP
#define _FORGE_TYPE_INTRINSICS_HPP

/// Forge Modules
#include "forge/type/tagged.hpp"

namespace Forge::Type {

    /// @brief Any Intrinsic Typing.
    struct Any : public Abstract<Any> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        /// @brief This will always resolve an entity.
        Entity lookup(const $::String::View&) const final;

        /// @brief Ensures all applications of operators return "Any" types.
        Erased apply(Operator::Kind) const final;
        Erased apply(Operator::Kind, const Erased&) const final;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Ensures all candidates resolve to "Any" types.
        inline bool m_unify(const Erased&, const Constraints&) const final { return true; }

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        virtual inline void m_print($::Stream::Output& os) const override { os << "Any"; }
    };

    /// @brief Error Intrinsic Typing.
    struct Failure : public Abstract<Failure, Any> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        inline void m_print($::Stream::Output& os) const final { os << "Failure"; }
    };

    /// @brief Void Type Hint.
    struct None : public Abstract<None> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        inline constexpr Lattice lattice() const noexcept final { return Fact::NIL_ANY; }
        inline constexpr $::Ternary truthiness() const noexcept final { return false; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles validating "Void" shapes.
         * @param shape                     Shape to validate.
         */
        inline constexpr bool m_extends(Shape::Underlying shape) const noexcept final {
            return shape == Shape::Lookup<Value::Void>();
        }

        /**
         * @brief Handles unifying the type.
         * @param candidate                 Candidate to unify.
         */
        inline bool m_unify(const Erased& candidate, const Constraints&) const final { return candidate->is<None>(); }

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        void m_print($::Stream::Output& os) const final;
    };

    /// @brief Unset Intrinsic Typing.
    struct Unset : public Abstract<Unset> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        /// @brief This will always resolve an empty entity.
        Entity lookup(const $::String::View&) const final;

        /// @brief Ensures all applications of operators return "Unset" types.
        Erased apply(Operator::Kind) const final { return m_clone(); }
        Erased apply(Operator::Kind, const Erased&) const final { return m_clone(); }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Since this is our unset typing, values should not be subtyped from here.
        inline bool m_unify(const Erased&, const Constraints&) const final { return false; }

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        inline void m_print($::Stream::Output& os) const final { os << "Unset"; }
    };

}  // namespace Forge::Type

#endif
