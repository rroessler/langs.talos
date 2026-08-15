#ifndef _XTDLIB_LAMBDA_VISITOR_HPP
#define _XTDLIB_LAMBDA_VISITOR_HPP

namespace $::Lambda {

/// @brief A simple template for lambda overloads.
template <class... Ts> struct Visitor : Ts... {
  using Ts::operator()...;
};

} // namespace $::Lambda

#endif
