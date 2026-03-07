#ifndef _TALOS_FUNCTION_NATIVE_HPP
#define _TALOS_FUNCTION_NATIVE_HPP

/// Talos Modules
#include "talos/function/callback.hpp"
#include "talos/object/abstract.hpp"

namespace Talos {

    /// @brief Native Function Attributes.
    template <>
    struct Object::Attributes<Function::Native> {
        //  PROPERTIES  //

        /// @brief Associated native resource.
        $::URI::Buffer resource = $::URI::Anonymous().buffer();

        /// @brief The bound callback value.
        Function::Callback callback = [](Runtime::Isolate*, const Function::Arguments&) -> Value::Any {
            return Value::Void();  // declare a simple value here as necessary
        };

        //  CONSTRUCTORS  //

        /// @brief Constructs an empty native function.
        explicit Attributes() = default;

        /**
         * @brief Constructs a native with an "eval:..." description.
         * @param callback              Callback to bind.
         * @param description           Description to use.
         */
        explicit Attributes(Function::Callback callback, const $::String::View& description) :
            Attributes(callback, $::URI::Evaluate("{0}()", description)) {}

        /**
         * @brief Constructs a native with an "eval:..." description.
         * @param callback              Callback to bind.
         * @param category              Category to bind.
         * @param field                 Member field.
         */
        explicit Attributes(Function::Callback callback, const $::String::View& parent, const $::String::View& field) :
            Attributes(callback, fmt::format("{0}.{1}", parent, field)) {}

        /**
         * @brief Constructs a native function.
         * @param callback              Callback to bind.
         * @param resource              Resource to bind.
         */
        explicit Attributes(
            Function::Callback callback, const $::URI::Buffer& resource = $::URI::Anonymous().buffer()) :
            resource(resource), callback(callback) {}
    };

    /// @brief Native Function Interface.
    struct Function::Native : public Object::Abstract<Function::Native> {
        //  TYPEDEFS  //

        /// @brief Allow base function access.
        friend struct Dynamic;

        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        /// @brief Gets the arity of a native function.
        inline constexpr uint64_t arity() const noexcept { return 0; }

        /// @brief Gets the adicity of a native function.
        inline constexpr uint64_t adicity() const noexcept { return SIZE_MAX; }

        inline constexpr Value::Any receiver() const noexcept { return Value::Void(); }
        inline constexpr Callback callback() const noexcept { return m_attrs()->callback; }
        inline constexpr $::URI::View resource() const noexcept { return m_attrs()->resource; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handlers yielding natives safely.
         * @param self                          Native instance.
         * @param yield                         Yield callback.
         */
        static inline void m_yield(const Native&, const Globals::Each&) {}
    };

}  // namespace Talos

#endif
