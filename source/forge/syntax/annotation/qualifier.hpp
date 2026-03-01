#ifndef _FORGE_ANNOTATION_QUALIFIER_HPP
#define _FORGE_ANNOTATION_QUALIFIER_HPP

/// Syntax Includes
#include "forge/syntax/annotation/generics.hpp"
#include "forge/syntax/literal/identifier.hpp"

namespace Forge::Syntax {

    /// @brief Qualifier Annotation.
    class Qualifier : public Abstract<Qualifier, Annotation> {
        //  PROPERTIES  //

        /// @brief Generic template arguments.
        Specialization m_types = {};

        /// @brief Qualifier identifiers chain.
        std::vector<Identifier*> m_segments;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a qualifier annotation.
         * @param segment                   Identifier segment.
         */
        explicit Qualifier(Identifier* segment) : Qualifier(segment, segment->traits()->location()) {}

        /**
         * @brief Constructs a qualifier annotation.
         * @param segment                   Identifier segment.
         * @param location                  Resource location.
         */
        explicit Qualifier(Identifier* segment, const Bounds& location) : Abstract(location), m_segments({ segment }) {}

        /**
         * @brief Constructs a qualifier annotation.
         * @param segments                  Identifier segments.
         * @param location                  Resource location.
         */
        explicit Qualifier(const std::vector<Identifier*>& segments, const Bounds& location = {}) :
            Abstract(location), m_types({}), m_segments(segments) {}

        /**
         * @brief Constructs a qualifier annotation.
         * @param segments                  Identifier segments.
         * @param types                     Typed arguments.
         * @param location                  Resource location.
         */
        explicit Qualifier(
            const std::vector<Identifier*>& segments, const Specialization& types = {}, const Bounds& location = {}) :
            Abstract(location), m_types(types), m_segments(segments) {}

        //  PUBLIC METHODS  //

        inline constexpr const Specialization& types() const noexcept { return m_types; }
        inline constexpr const std::vector<Identifier*>& segments() const noexcept { return m_segments; }
    };

}  // namespace Forge::Syntax

#endif
