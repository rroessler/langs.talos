#ifndef _TALOS_TYPE_CONTEXT_HPP
#define _TALOS_TYPE_CONTEXT_HPP

/// Talos Modules
#include "talos/relint/metadata.hpp"
#include "talos/type/entity.hpp"
#include "talos/variable/captures.hpp"

/// Type Modules
#include "talos/type/utility/intrinsics.hpp"

namespace Talos::Type {

    /// @brief Type Exports Alias.
    using Exports = $::Record<Entity>;

    /// @brief Type Environment Context.
    class Context {
        //  TYPEDEFS  //

        /// @brief Allow the type-analyzer internal access.
        friend class Analyzer;

        //  PROPERTIES  //

        /// @brief Underlying monotype value.
        Erased m_monotype = nullptr;

        /// @brief All exported types.
        Exports m_exports = {};

        /// @brief Available variable captures.
        Variable::Captures m_captures = {};

        /// @brief Additional syntax metadata.
        $::Ptr::Unique<Relint::Metadata> m_mirrors = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a type-context.
         * @param monotype              Dynamic monotyping.
         */
        explicit Context(const Erased& monotype = nullptr) : m_monotype(monotype) {}

        //  PUBLIC METHODS  //

        inline constexpr Erased monotype() const noexcept { return m_monotype; }
        inline constexpr bool dynamic() const noexcept { return m_monotype != nullptr; }
        inline constexpr bool failure() const noexcept { return dynamic() && m_monotype->is<Failure>(); }

        inline constexpr Exports& exports() noexcept { return m_exports; }
        inline constexpr const Exports& exports() const noexcept { return m_exports; }

        inline constexpr $::Ptr::Unique<Relint::Metadata>& mirrors() noexcept { return m_mirrors; }
        inline constexpr const Relint::Metadata* mirrors() const noexcept { return m_mirrors.get(); }

        inline constexpr Variable::Captures& captures() noexcept { return m_captures; }
        inline constexpr const Variable::Captures& captures() const noexcept { return m_captures; }
    };

}  // namespace Talos::Type

#endif
