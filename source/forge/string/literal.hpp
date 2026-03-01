#ifndef _FORGE_STRING_LITERAL_HPP
#define _FORGE_STRING_LITERAL_HPP

/// Forge Modules
#include "forge/string/dynamic.hpp"

namespace Forge::String::Literal {

    /**
     * @brief Handles safely formatting a message with arguments.
     * @param isolate                   Runtime isolate.
     * @param message                   Message to format.
     * @param arguments                 Format arguments.
     */
    Value::Any style(Runtime::Isolate* isolate, String::Dynamic message, Arguments&& arguments);
    Value::Any style(Runtime::Isolate* isolate, const $::String::View& message, Arguments&& arguments);
    Value::Any style(Runtime::Isolate* isolate, String::Dynamic message, const Function::Arguments& arguments);
    Value::Any style(Runtime::Isolate* isolate, const $::String::View& message, const Function::Arguments& arguments);

}  // namespace Forge::String::Literal

#endif
