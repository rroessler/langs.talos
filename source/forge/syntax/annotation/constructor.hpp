#ifndef _FORGE_ANNOTATION_CONSTRUCTOR_HPP
#define _FORGE_ANNOTATION_CONSTRUCTOR_HPP

/// Forge Modules
#include "forge/syntax/annotation/generics.hpp"
#include "forge/syntax/annotation/parameters.hpp"

namespace Forge::Syntax {

    /// @brief Signature Constructor Node.
    class Constructor : public Abstract<Constructor, Annotation> {
        //  PROPERTIES  //

        /// @brief Generics template to be used.
        Template m_generics = {};

        /// @brief Associated signature parameters.
        Parameters* m_parameters = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a defaulted constructor.
         * @param location                  Resource location.
         */
        explicit Constructor(const Bounds& location = {}) : Abstract(location) {}

        /**
         * @brief Constructs a defaulted constructor.
         * @param parameters                Signature parameters.
         * @param location                  Resource location.
         */
        explicit Constructor(Parameters* parameters, const Bounds& location = {}) :
            Abstract(location), m_parameters(parameters) {}

        /**
         * @brief Constructs a defaulted constructor.
         * @param generics                  Template generics.
         * @param location                  Resource location.
         */
        explicit Constructor(const Template& generics, const Bounds& location = {}) :
            Abstract(location), m_generics(generics) {}

        /**
         * @brief Constructs a defaulted constructor.
         * @param generics                  Template generics.
         * @param parameters                Signature parameters.
         * @param location                  Resource location.
         */
        explicit Constructor(const Template& generics, Parameters* parameters, const Bounds& location = {}) :
            Abstract(location), m_generics(generics), m_parameters(parameters) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the template generics available.
        inline constexpr const Template& generics() const noexcept { return m_generics; }

        /// @brief Gets the parameters available.
        inline constexpr const Parameters* parameters() const noexcept { return m_parameters; }

        /// @brief Gets the underlying spread parameter.
        inline constexpr Variable* spread() const noexcept { return m_parameters ? m_parameters->spread() : nullptr; }

        /// @brief Gets the minimum parameters sizing.
        inline size_t arity() const noexcept { return m_parameters ? m_parameters->arity() : 0; }

        /// @brief Gets the maximum parameters sizing.
        inline size_t adicity() const noexcept { return m_parameters ? m_parameters->adicity() : 0; }
    };

}  // namespace Forge::Syntax

#endif
