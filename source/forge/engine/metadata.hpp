#ifndef _FORGE_ENGINE_METADATA_HPP
#define _FORGE_ENGINE_METADATA_HPP

/// Forge Modules
#include "forge/async/thenable.hpp"
#include "forge/engine/exports.hpp"
#include "forge/module/metadata.hpp"

namespace Forge::Module {

    /// @brief Constructs a set of export metadata.
    template <>
    class Metadata::Attributes<Phase::EXPORTED> : public Metadata, public Engine::Exports {
        //  PROPERTIES  //

        /// @brief The resolvable final exports.
        $::Ptr::Unique<Async::Thenable> m_thenable = $::New().unique<Async::Thenable>();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a set of exports.
        explicit Attributes() = default;

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying thenable instance.
        inline Async::Thenable* deferred() const noexcept { return m_thenable.get(); }

        /**
         * @brief Handles waiting for the final exports.
         * @param isolate               Runtime isolate.
         */
        inline Value::Any await(Runtime::Isolate* isolate) const noexcept { return deferred()->await(isolate); }
    };

}  // namespace Forge::Module

#endif
