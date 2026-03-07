#ifndef _TALOS_LITERAL_RECORD_HPP
#define _TALOS_LITERAL_RECORD_HPP

/// Syntax Modules
#include "talos/syntax/declaration/variable.hpp"

namespace Talos::Syntax {

    /// @brief Record Literal Node.
    class Record : public Abstract<Record, Expression> {
        //  PROPERTIES  //

        /// @brief Record elements.
        std::vector<Variable*> m_elements = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a list literal.
         * @param location                  Resource location.
         */
        explicit Record(const Bounds& location = {}) : Abstract(location) {}

        /**
         * @brief Constructs a list literal.
         * @param fields                    Record fields.
         * @param location                  Resource location.
         */
        explicit Record(const std::vector<Variable*>& elements, const Bounds& location = {}) :
            Abstract(location), m_elements(elements) {}

        //  PUBLIC METHODS  //

        inline constexpr bool empty() const noexcept { return m_elements.empty(); }
        inline constexpr size_t size() const noexcept { return m_elements.size(); }

        /// @brief Gets the underlying elements.
        inline constexpr const std::vector<Variable*>& elements() const noexcept { return m_elements; }
    };

}  // namespace Talos::Syntax

#endif
