#ifndef _FORGE_MODULE_DRAFTS_HPP
#define _FORGE_MODULE_DRAFTS_HPP

/// Forge Includes
#include "forge/module/interface.hpp"
#include "forge/value/symbol.hpp"

namespace Forge::Import {

    /// @brief Module Drafts Container.
    class Drafts {
        //  PROPERTIES  //

        /// @brief Drafts modification mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Bound module drafts.
        $::Map<Value::Symbol, $::Ptr::Unique<Module::Interface>> m_modules = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a set of drafts.
        explicit Drafts() = default;

        //  PUBLIC METHODS  //

        /// @brief Removes all bound modules.
        inline void clear() { m_modules.clear(); }

        /// @brief Gets all the available drafts for iteration.
        inline constexpr auto each() const noexcept { return m_modules | std::views::values; }

        /**
         * @brief Checks if drafts contains a resource.
         * @param resource              Resource value.
         */
        inline bool contains(Value::Symbol resource) const { return m_modules.contains(resource); }

        /**
         * @brief Attempts getting a resource.
         * @param resource              Resource value.
         */
        inline Module::Interface* lookup(Value::Symbol resource) const {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);  // pre-lock now
            auto iterator = m_modules.find(resource);   // attempt finding
            return iterator == m_modules.end() ? nullptr : iterator->second.get();
        }

        /**
         * @brief Handles emplacing modules.
         * @param module                Module to emplace.
         */
        inline Module::Interface* emplace($::Ptr::Unique<Module::Interface>&& module) {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
            auto symbol = Value::Symbol(module->resource());
            if (contains(symbol)) return m_modules.at(symbol).get();
            return m_modules.emplace(symbol, std::move(module)).first->second.get();
        }

        /**
         * @brief Handles removing modules.
         * @param resource              Resource value.
         */
        inline void remove(Value::Symbol resource) {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
            m_modules.erase(resource);  // and remove
        }
    };

}  // namespace Forge::Import

#endif
