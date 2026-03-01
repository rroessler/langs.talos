#ifndef _FORGE_LIFECYCLE_SCOPE_HPP
#define _FORGE_LIFECYCLE_SCOPE_HPP

/// Forge Modules
#include "forge/forward/lifecycle.hpp"
#include "forge/forward/runtime.hpp"

namespace Forge::Lifecycle {

    /// @brief Scoped Lifecycle Handler.
    class Scope : public XI::Define<Scope, XI::Unique> {
        //  PROPERTIES  //

        /// @brief The lifecycle service.
        Lifecycle::Service* m_lifecycle;

        /// @brief Bound isolate instance.
        Runtime::Isolate* m_isolate;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a lifecycle scoping.
         * @param services          Services container.
         * @param isolate           Runtime isolate.
         */
        explicit Scope(Runtime::Isolate* isolate = nullptr);
        explicit Scope(XI::Container* services, Runtime::Isolate* isolate = nullptr);

        /// @brief Handles destructing the scoping.
        ~Scope();
    };

}  // namespace Forge::Lifecycle

#endif
