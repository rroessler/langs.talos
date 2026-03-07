#ifndef _TALOS_ANNOTATION_INTERFACE_HPP
#define _TALOS_ANNOTATION_INTERFACE_HPP

/// Syntax Modules
#include "talos/syntax/declaration/variable.hpp"

namespace Talos::Syntax {

    /// @brief Interface Annotation Node.
    class Interface : public Abstract<Interface, Annotation> {
        //  PROPERTIES  //

        /// @brief Record elements.
        std::vector<Syntax::Variable*> m_properties = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an empty interface.
         * @param location                  Resource location.
         */
        explicit Interface(const Bounds& location = {}) : Abstract(location) {}

        /**
         * @brief Constructs an interface annotation.
         * @param properties                Interface fields.
         * @param location                  Resource location.
         */
        explicit Interface(const std::vector<Syntax::Variable*>& properties, const Bounds& location = {}) :
            Abstract(location), m_properties(properties) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying elements.
        inline constexpr const std::vector<Syntax::Variable*>& properties() const noexcept { return m_properties; }
    };

}  // namespace Talos::Syntax

#endif
