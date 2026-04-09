#ifndef _TALOS_BUILTINS_EXCEPTION_HPP
#define _TALOS_BUILTINS_EXCEPTION_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/object/exception.hpp"

namespace Talos::Builtins {

    /// @brief Tagged Exception Builtin Traits.
    template <>
    struct Traits<Object::Exception> : public Define<Object::Exception, "Exception">,
                                       public Features<Adapter::FIELDS, Adapter::GLOBALS, Adapter::TYPEDEFS> {
        //  TYPEDEFS  //

        /// @brief Helper for constructing outputs.
        struct Field;
        struct Static;

       private:
        //  PROPERTIES  //

        /// @brief Available field descriptors.
        static Member::Storage m_members;

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "Exception" typing.
        static Type::Erased typing();

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Allows instantiating global types.
         * @param globals                   Global type-world.
         */
        static void m_typedefs(Type::World* globals);

        /**
         * @brief Handles instantiating globals.
         * @param isolate                   Runtime isolate.
         */
        static Value::Any m_globals(Runtime::Isolate* isolate);

        /**
         * @brief Handles looking up value fields.
         * @param self                      Self value.
         * @param symbol                    Field symbol.
         */
        static Member::View m_attributes(const Object::Exception& self, Value::Symbol symbol);
    };

}  // namespace Talos::Builtins

#endif
