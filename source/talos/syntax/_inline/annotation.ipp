#ifndef _TALOS_SYNTAX_ANNOTATION_IPP
#define _TALOS_SYNTAX_ANNOTATION_IPP

/// Talos Modules
#include "talos/parser/dispatch.hpp"

/// Annotation Modules
#include "talos/syntax/annotation/interface.hpp"
#include "talos/syntax/annotation/placeholder.hpp"
#include "talos/syntax/annotation/qualifier.hpp"
#include "talos/syntax/annotation/signature.hpp"

//  MACROS  //

#define TALOS_XX_ANNOTATION_NODES(X) \
    X(Qualifier)                     \
    X(Placeholder)                   \
    X(Parameters)                    \
    X(Constructor)                   \
    X(Signature)                     \
    X(Interface)

//  SPECIALIZATIONS  //

#define X(N, ...) TALOS_MM_PARSE_HINT(N, );
TALOS_XX_ANNOTATION_NODES(X)
#undef X

TALOS_MM_PARSE_DECL(Parameters, );
TALOS_MM_PARSE_DECL(Constructor, );
TALOS_MM_PARSE_DECL(Signature, );

#endif
