#ifndef _TALOS_STRING_LITERAL_HPP
#define _TALOS_STRING_LITERAL_HPP

/// Talos Modules
#include "talos/string/dynamic.hpp"

namespace Talos::String::Literal {

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

}  // namespace Talos::String::Literal

#endif
