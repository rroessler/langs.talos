#ifndef _TALOS_VALUE_FOLD_HPP
#define _TALOS_VALUE_FOLD_HPP

/// Talos Includes
#include "talos/forward/syntax.hpp"
#include "talos/number/tagged.hpp"

namespace Talos::Value {

/**
 * @brief Handles folding expression values.
 * @param node              Expression to fold.
 */
Value::Any Fold(const Syntax::Node *node);

/**
 * @brief Handles folding unary values.
 * @param kind              Operator to apply.
 * @param value             Value to fold.
 */
Value::Any Fold(Operator::Kind kind, const Value::Any &value);
Value::Any Fold(Operator::Kind kind, const Number::Tagged &value);

/**
 * @brief Handles folding binary values.
 * @param kind              Operator to apply.
 * @param left              Left-most value.
 * @param right             Right-most value.
 */
Value::Any Fold(Operator::Kind kind, const Value::Any &left, const Value::Any &right);
Value::Any Fold(Operator::Kind kind, const Number::Tagged &left, const Number::Tagged &right);

} // namespace Talos::Value

#endif
