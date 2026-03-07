#ifndef _TALOS_HANDLE_SCOPE_HPP
#define _TALOS_HANDLE_SCOPE_HPP

/// Talos Includes
#include "talos/forward/runtime.hpp"
#include "talos/handle/local.hpp"

namespace Talos::Handle {

    /// @brief Handle Scope Container.
    class Scope {
        //  TYPEDEFS  //

        /// @brief Allow locals internal access.
        template <std::derived_from<Value::Any> T>
        friend class Local;

        //  PROPERTIES  //

        /// @brief Attached thread isolate.
        Runtime::Isolate* m_isolate;

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow moving, copying or anything.
        explicit Scope(...) = delete;

        /**
         * @brief Constructs a handle scope.
         * @param isolate               Thread isolate.
         */
        explicit Scope(Runtime::Isolate* isolate) : m_isolate(isolate) {}

        //  OPERATOR METHODS  //

        /**
         * @brief Handles constructing local-handles.
         * @tparam T                    Type of value.
         * @param value                 Value to scope.
         */
        template <std::derived_from<Value::Any> T>
        inline constexpr Local<T> operator()(T value) {
            return Local<T>(this, value);
        }
    };

}  // namespace Talos::Handle

#endif
