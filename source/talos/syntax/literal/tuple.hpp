#ifndef _TALOS_LITERAL_TUPLE_HPP
#define _TALOS_LITERAL_TUPLE_HPP

/// Talos Modules
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Tuple Literal Node.
    class Tuple : public Abstract<Tuple, Expression> {
        //  PROPERTIES  //

        /// @brief List elements.
        std::vector<Expression*> m_elements = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a list literal.
         * @param location                  Resource location.
         */
        explicit Tuple(const Bounds& location = {}) : Abstract(location) {}

        /**
         * @brief Constructs a list literal.
         * @param elements                  List elements.
         * @param location                  Resource location.
         */
        explicit Tuple(const std::vector<Expression*>& elements, const Bounds& location = {}) :
            Abstract(location), m_elements(elements) {}

        //  PUBLIC METHODS  //

        inline constexpr bool empty() const noexcept { return m_elements.empty(); }
        inline constexpr size_t size() const noexcept { return m_elements.size(); }

        /// @brief Gets the underlying elements.
        inline constexpr const std::vector<Expression*>& elements() const noexcept { return m_elements; }
    };

}  // namespace Talos::Syntax

#endif
