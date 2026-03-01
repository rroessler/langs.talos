#ifndef _FORGE_SYNTAX_ANNOTATION_IPP
#define _FORGE_SYNTAX_ANNOTATION_IPP

/// Forge Modules
#include "forge/parser/dispatch.hpp"

/// Annotation Modules
#include "forge/syntax/annotation/interface.hpp"
#include "forge/syntax/annotation/placeholder.hpp"
#include "forge/syntax/annotation/qualifier.hpp"
#include "forge/syntax/annotation/signature.hpp"

//  MACROS  //

#define FORGE_XX_ANNOTATION_NODES(X) \
    X(Qualifier)                     \
    X(Placeholder)                   \
    X(Parameters)                    \
    X(Constructor)                   \
    X(Signature)                     \
    X(Interface)

//  SPECIALIZATIONS  //

#define X(N, ...) FORGE_MM_PARSE_HINT(N, );
FORGE_XX_ANNOTATION_NODES(X)
#undef X

FORGE_MM_PARSE_DECL(Parameters, );
FORGE_MM_PARSE_DECL(Constructor, );
FORGE_MM_PARSE_DECL(Signature, );

#endif
