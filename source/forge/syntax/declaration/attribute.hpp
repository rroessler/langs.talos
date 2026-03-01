#ifndef _FORGE_DECLARATION_ATTRIBUTE_HPP
#define _FORGE_DECLARATION_ATTRIBUTE_HPP

/// Forge Modules
#include "forge/reflect/category.hpp"
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Compile Time Attribute Node.
    class $_ABSTRACT Attribute : public Passthrough<Attribute> {
        //  PROPERTIES  //

        /// @brief Associated compile-time category.
        Reflect::Category m_category;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a compile-time attribute.
         * @param tag                       Node runtime tag.
         * @param category                  Reflection category.
         * @param location                  Resource location.
         */
        explicit Attribute($::RTTI::Tag tag, Reflect::Category category, const Bounds& location = {}) :
            Passthrough<Attribute>(tag, location), m_category(category) {}

        //  PUBLIC METHODS  //

        inline constexpr Reflect::Category category() const noexcept { return m_category; }
    };

}  // namespace Forge::Syntax

#endif
