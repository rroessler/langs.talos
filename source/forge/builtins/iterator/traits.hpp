#ifndef _FORGE_BUILTINS_ITERATOR_HPP
#define _FORGE_BUILTINS_ITERATOR_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"
#include "forge/iterable/iterator.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_ITERATOR(X) \
    X(from)                          \
    X(empty)                         \
    X(dynamic)

#define FORGE_XX_FIELDS_ITERATOR(X) \
    X(done)                         \
    X(next)                         \
    X(index)

//  NAMESPACES  //

namespace Forge::Builtins {

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

}  // namespace Forge::Builtins

#endif
