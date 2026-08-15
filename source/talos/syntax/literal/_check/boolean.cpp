/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(True, , ) {}
TALOS_MM_CAPTURE_NODE(False, , ) {}

TALOS_MM_CHECK_NODE(True, , ) { return Type::New::boolean(); }
TALOS_MM_CHECK_NODE(False, , ) { return Type::New::boolean(); }
