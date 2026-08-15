#ifndef _TALOS_NUMBER_BIGNUM_HPP
#define _TALOS_NUMBER_BIGNUM_HPP

/// Talos Includes
#include "talos/object/mixin.hpp"

namespace Talos {

/// TODO: Implement a "Bignum" object.

/// @brief Large Number Attributes.
template <> struct Object::Wrapper<Number::Bignum> {};

/// @brief Arbitrary Precision Number.
struct Number::Bignum : public Object::Mixin<Bignum> {};

} // namespace Talos

#endif
