#ifndef _XLSP_PROTOCOL_TRACE_HPP
#define _XLSP_PROTOCOL_TRACE_HPP

/// XLSP Includes
#include "xlsp/forward/protocol.hpp"

//  X-MACROS  //

/// @brief Available LSP trace values.
#define XX_TRACE_VALUES(X) \
  X(OFF, "off")            \
  X(MESSAGES, "messages")  \
  X(VERBOSE, "verbose")

//  NAMESPACES  //

namespace XLSP::Trace {

//  TYPEDEFS  //

/// @brief Available encoding types.
$_XX_ENUM_CLASS(Value, uint8_t, XX_TRACE_VALUES);

//  PUBLIC METHODS  //

/**
 * @brief Resolves a suitable trace value.
 * @param view                          Trace view.
 */
static constexpr Value resolve(const $::String::View &view) {
#define X(N, S, ...)                     \
  case XH::FNV::U32(S): return Value::N;
  switch (XH::FNV::U32(view)) { XX_TRACE_VALUES(X) default : return Value::OFF; }
#undef X
}

/**
 * @brief Converts a trace-value to a string.
 * @param value                         Trace value.
 */
static constexpr $::String::View format(const Value &trace) {
#define X(N, S, ...)       \
  case Value::N: return S;
  switch (trace) { XX_TRACE_VALUES(X) default : return "off"; }
#undef X
}

} // namespace XLSP::Trace

//  UNDEFINES  //

#undef XX_TRACE_VALUES

#endif
