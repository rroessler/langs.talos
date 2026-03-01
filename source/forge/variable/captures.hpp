#ifndef _FORGE_VARIABLE_CAPTURES_HPP
#define _FORGE_VARIABLE_CAPTURES_HPP

/// Forge Modules
#include "forge/forward/syntax.hpp"
#include "forge/forward/variable.hpp"

namespace Forge::Variable {

    /// @brief Capture Identifier Reference.
    using Entry = uintptr_t;

    /// @brief Available Variable Extent Values.
    enum class Extent : uint8_t { GLOBAL, LOCAL, UPVALUE, LEAKED };

    /// @brief Contains all captured variables.
    class Captures {
        //  PROPERTIES  //

        /// @brief Currently bound captures available.
        $::Map<Entry, Extent> m_bound = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted set of captures.
        constexpr Captures() = default;

        //  PUBLIC METHODS  //

        /**
         * @brief Resolves a variable extent.
         * @param variable              Variable to resolve.
         */
        inline constexpr Extent resolve(const Syntax::Node* variable) const noexcept {
            auto encoded = m_encode(variable);  // prepare the key now
            return $_ASSERT(m_bound.contains(encoded)), m_bound.at(encoded);
        }

        /**
         * @brief Declares a variable initially.
         * @param variable              Variable identifier.
         */
        inline constexpr Entry declare(const Syntax::Node* variable) {
            return m_mark(m_encode(variable), Extent::LOCAL);
        }

        /**
         * @brief Declares a global variable.
         * @param variable              Variable identifier.
         */
        inline constexpr void global(const Syntax::Identifier* variable) { m_mark(m_encode(variable), Extent::GLOBAL); }

        /**
         * @brief Marks an identifier as local.
         * @param identifier            Identifier to mark.
         * @param local                 Local variable entry.
         */
        inline constexpr void mark(const Syntax::Identifier* identifier, Entry local) {
            m_mark(m_encode(identifier), local, Extent::LOCAL);
        }

        /**
         * @brief Marks an identifier as a leaked.
         * @param identifier            Identifier to mark.
         * @param leaked                Leaked variable entry.
         */
        inline constexpr void leak(const Syntax::Identifier* identifier, Entry leaked) {
            m_mark(m_encode(identifier), leaked, Extent::UPVALUE);
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding variables as bound variables.
         * @param variable              Variable to encode.
         */
        template <class T>
        inline constexpr Entry m_encode(const T* variable) const noexcept {
            return reinterpret_cast<Entry>(variable);
        }

        /**
         * @brief Handles marking simple variables.
         * @param variable              Variable to mark.
         * @param extent                Extent to mark.
         */
        inline constexpr Entry m_mark(Entry variable, Extent extent) { return m_mark(variable, 0, extent), variable; }

        /**
         * @brief Handles marking bound variables.
         * @param variable              Variable to mark.
         * @param leaked                Leaked variable.
         * @param extent                Extent to mark.
         */
        inline constexpr void m_mark(Entry variable, Entry leaked, Extent extent) {
            $_ASSERT(extent != Extent::LEAKED, "Cannot manually mark leaked variables");
            m_bound.emplace(variable, extent);  // mark the variable now
            if (extent == Extent::UPVALUE) m_bound.at(leaked) = Extent::LEAKED;
        }
    };

}  // namespace Forge::Variable

#endif
