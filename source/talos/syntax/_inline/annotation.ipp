#ifndef _TALOS_SYNTAX_ANNOTATION_IPP
#define _TALOS_SYNTAX_ANNOTATION_IPP

/// Talos Includes
#include "talos/parser/dispatch.hpp"

/// Parser Includes
#include "talos/parser/_inline/macros.ipp"

/// Annotation Includes
#include "talos/syntax/annotation/constructor.hpp"
#include "talos/syntax/annotation/interface.hpp"
#include "talos/syntax/annotation/parameters.hpp"
#include "talos/syntax/annotation/placeholder.hpp"
#include "talos/syntax/annotation/qualifier.hpp"
#include "talos/syntax/annotation/signature.hpp"

//  MACROS  //

/// @brief All available type-annotation nodes.
#define TALOS_XX_ANNOTATION_NODES(X) \
  X(Qualifier)                       \
  X(Placeholder)                     \
  X(Parameters)                      \
  X(Constructor)                     \
  X(Signature)                       \
  X(Interface)

//  SPECIALIZATIONS  //

#define X(N, ...) TALOS_MM_PARSE_HINT(N, );
TALOS_XX_ANNOTATION_NODES(X)
#undef X

TALOS_MM_PARSE_DECL(Parameters, );
TALOS_MM_PARSE_DECL(Constructor, );
TALOS_MM_PARSE_DECL(Signature, );

#endif
