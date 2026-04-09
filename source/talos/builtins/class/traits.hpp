#ifndef _TALOS_BUILTINS_CLASS_HPP
#define _TALOS_BUILTINS_CLASS_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/object/class.hpp"

namespace Talos::Builtins {

    /// @brief Tagged Class Builtin Traits.
    template <>
    struct Traits<Object::Class> : public Define<Object::Class, "Class">, public Features<Adapter::FIELDS> {
       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles looking up class fields.
         * @param self                      Object class.
         * @param symbol                    Field symbol.
         */
        static Member::View m_attributes(const Object::Class& self, Value::Symbol symbol);
    };

}  // namespace Talos::Builtins

#endif
