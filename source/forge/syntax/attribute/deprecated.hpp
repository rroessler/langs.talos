#ifndef _FORGE_ATTRIBUTE_DEPRECATED_HPP
#define _FORGE_ATTRIBUTE_DEPRECATED_HPP

/// Forge Modules
#include "forge/diagnostic/traits.hpp"

/// Syntax Modules
#include "forge/syntax/declaration/attribute.hpp"

namespace Forge::Syntax {

    /// @brief Compile Time Deprecation Node.
    class Deprecated : public Abstract<Deprecated, Attribute> {
        //  PROPERTIES  //

        /// @brief The underlying deprecation message.
        $::String::View m_message;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a deprecated attribute.
         * @param location                      Resource location.
         */
        explicit Deprecated(const Bounds& location = {}) : Deprecated(Diagnostic::Traits::message(9000101), location) {}

        /**
         * @brief Constructs a deprecated attribute.
         * @param message                       Deprecation message.
         * @param location                      Resource location.
         */
        explicit Deprecated(const $::String::View& message, const Bounds& location = {}) :
            Abstract(Reflect::Category::DEPRECATED, location), m_message(message) {}

        //  PUBLIC METHODS  //

        /// @brief The underlying attribute message.
        inline constexpr $::String::View message() const noexcept { return m_message; }
    };

}  // namespace Forge::Syntax

#endif
