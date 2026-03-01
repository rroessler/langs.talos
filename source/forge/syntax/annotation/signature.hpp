#ifndef _FORGE_ANNOTATION_SIGNATURE_HPP
#define _FORGE_ANNOTATION_SIGNATURE_HPP

/// Forge Modules
#include "forge/syntax/annotation/constructor.hpp"

namespace Forge::Syntax {

    /// @brief Signature Annotation Node.
    class Signature : public Abstract<Signature, Annotation> {
        //  PROPERTIES  //

        /// @brief Return typing.
        Annotation* m_returns;

        /// @brief Signature constructor.
        Constructor* m_prototype;

        /// @brief A defaulted parameter list available.
        static inline Parameters::List m_defaulted = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a signature annotation.
         * @param prototype                 Signature prototype.
         * @param returns                   Expected return type.
         */
        explicit Signature(Constructor* prototype, Annotation* returns) :
            Signature(prototype, returns, prototype->traits()->location()) {}

        /**
         * @brief Constructs a signature annotation.
         * @param prototype                 Signature prototype.
         * @param returns                   Expected return type.
         * @param location                  Resource location.
         */
        explicit Signature(Constructor* prototype, Annotation* returns, const Bounds& location) :
            Abstract(location), m_returns(returns), m_prototype(prototype) {}

        //  PUBLIC METHODS  //

        inline constexpr Annotation* returns() const noexcept { return m_returns; }
        inline constexpr Variable* spread() const noexcept { return m_prototype->spread(); }
        inline constexpr const Constructor* prototype() const noexcept { return m_prototype; }
        inline constexpr const Template& generics() const noexcept { return m_prototype->generics(); }
        inline constexpr const Parameters::List& parameters() const noexcept {
            return m_prototype->parameters() ? m_prototype->parameters()->list() : m_defaulted;
        }

        inline constexpr size_t arity() const noexcept { return m_prototype->arity(); }
        inline constexpr size_t adicity() const noexcept { return m_prototype->adicity(); }
    };

}  // namespace Forge::Syntax

#endif
