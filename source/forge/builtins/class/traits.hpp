#ifndef _FORGE_BUILTINS_CLASS_HPP
#define _FORGE_BUILTINS_CLASS_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"
#include "forge/object/class.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_CLASS(X)
#define FORGE_XX_FIELDS_CLASS(X)

//  NAMESPACES  //

namespace Forge::Builtins {

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

}  // namespace Forge::Builtins

#endif
