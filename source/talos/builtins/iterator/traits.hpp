#ifndef _TALOS_BUILTINS_ITERATOR_HPP
#define _TALOS_BUILTINS_ITERATOR_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/iterable/iterator.hpp"

namespace Talos::Builtins {

    /// @brief Iterator Builtin Traits.
    template <>
    struct Traits<Iterable::Iterator> : public Define<Iterable::Iterator, "Iterator">,
                                        public Features<Adapter::FIELDS, Adapter::GLOBALS, Adapter::TYPEDEFS> {
       protected:
        //  TYPEDEFS  //

        /// @brief Helper for constructing outputs.
        struct Apply;
        struct Field;
        struct Static;

       private:
        //  PROPERTIES  //

        /// @brief Available field descriptors.
        static Member::Storage m_members;

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "Iterator" typing.
        static Type::Erased typing();

        /// @brief Gets the underlying "Generator" typing.
        static $::Ptr::Shared<Type::Generic> generator();

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
        static Member::View m_attributes(const Iterable::Iterator& self, Value::Symbol symbol);
    };

}  // namespace Talos::Builtins

#endif
