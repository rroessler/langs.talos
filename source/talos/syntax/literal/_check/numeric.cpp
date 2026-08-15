/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Numeric, , ) {}
TALOS_MM_CHECK_NODE(Numeric, , ) { return Type::New::number(); }
