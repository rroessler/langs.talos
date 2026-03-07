#ifndef _TALOS_ATTRIBUTE_OVERLOAD_HPP
#define _TALOS_ATTRIBUTE_OVERLOAD_HPP

/// Syntax Modules
#include "talos/syntax/annotation/signature.hpp"
#include "talos/syntax/declaration/attribute.hpp"

namespace Talos::Syntax {

    /// @brief Compile Time Overload Node.
    class Overload : public Abstract<Overload, Attribute> {
        //  PROPERTIES  //

        /// @brief The overload signature to bind.
        Signature* m_signature;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an overload attribute.
         * @param signature                 Signature to overload.
         * @param location                  Resource location.
         */
        explicit Overload(Signature* signature, const Bounds& location = {}) :
            Abstract(Reflect::Category::OVERLOAD, location), m_signature(signature) {}

        //  PUBLIC METHODS  //

        /// @brief The overload signature annotation.
        inline constexpr const Signature* signature() const noexcept { return m_signature; }
    };

}  // namespace Talos::Syntax

#endif
