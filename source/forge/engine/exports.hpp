#ifndef _FORGE_ENGINE_EXPORTS_HPP
#define _FORGE_ENGINE_EXPORTS_HPP

/// C++ Modules
#include <stack>

/// Forge Modules
#include "forge/forward/engine.hpp"
#include "forge/value/void.hpp"

namespace Forge::Engine {

    /// @brief Engine Exports Container.
    class Exports {
        //  PROPERTIES  //

        /// @brief Currently exported values.
        std::vector<Value::Any> m_scopes = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty set of exports.
        explicit Exports() = default;

        //  PUBLIC METHODS  //

        /**
         * @brief Begins a new set of exports.
         * @param isolate                   Runtime isolate.
         */
        Value::Any open(Isolate* isolate);

        /// @brief Closes a set of exports.
        Value::Any close();

        /// @brief Gets the available scopes.
        inline constexpr std::vector<Value::Any>& scopes() noexcept { return m_scopes; }
        inline constexpr const std::vector<Value::Any>& scopes() const noexcept { return m_scopes; }

        /// @brief Gets the current exports level.
        inline constexpr Value::Any current() const noexcept {
            return m_scopes.empty() ? Value::Void() : m_scopes.back();
        }
    };

}  // namespace Forge::Engine

#endif
