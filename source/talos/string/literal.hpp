#ifndef _TALOS_STRING_LITERAL_HPP
#define _TALOS_STRING_LITERAL_HPP

/// Talos Includes
#include "talos/string/common.hpp"

/// Forward Definitions
$_FWD(Talos::String, using Args = fmt::dynamic_format_arg_store<fmt::format_context>)

namespace Talos::String::Literal {

/**
 * @brief Handles safely formatting a message with arguments.
 * @param isolate                   Runtime isolate.
 * @param message                   Message to format.
 * @param args                      Format arguments.
 */
Value::Any style(Runtime::Isolate *isolate, const String::Any &message, Args &&args);
Value::Any style(Runtime::Isolate *isolate, const $::String::View &message, Args &&args);
Value::Any style(Runtime::Isolate *isolate, const String::Any &message, const Function::Args &args);
Value::Any style(Runtime::Isolate *isolate, const $::String::View &message, const Function::Args &args);

} // namespace Talos::String::Literal

#endif
