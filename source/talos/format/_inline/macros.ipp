#ifndef _TALOS_FORMAT_MACROS_IPP
#define _TALOS_FORMAT_MACROS_IPP

/// Talos Includes
#include "talos/format/dispatch.hpp"
#include "talos/syntax/visitor.hpp"

//  MACROS  //

#define TALOS_MM_FORMAT_FWD(N, T, ...)                                                            \
  template <> Talos::Format::Piece *Talos::Format::Dispatch::m_##N<Talos::Syntax::T>(__VA_ARGS__)

#define TALOS_MM_FORMAT_DECL(T, R, ...) TALOS_MM_FORMAT_FWD(declaration, T, Reader *R)
#define TALOS_MM_FORMAT_STMT(T, R, G, ...) TALOS_MM_FORMAT_FWD(statement, T, Reader *R, Piece::Group *G)
#define TALOS_MM_FORMAT_HINT(T, R, ...) TALOS_MM_FORMAT_FWD(annotation, T, Reader *R)
#define TALOS_MM_FORMAT_PREFIX(T, R, ...) TALOS_MM_FORMAT_FWD(prefix, T, Reader *R, bool)
#define TALOS_MM_FORMAT_INFIX(T, R, E, ...) TALOS_MM_FORMAT_FWD(infix, T, Reader *R, Piece *E, bool)

//  SPECIALIZATIONS  //

TALOS_MM_FORMAT_HINT(Node, , );
TALOS_MM_FORMAT_DECL(Node, , );
TALOS_MM_FORMAT_STMT(Node, , , );

#define X(N, ...) TALOS_MM_FORMAT_HINT(N, , );
TALOS_XX_ANNOTATION_NODES(X)
#undef X

#define X(N, ...) TALOS_MM_FORMAT_DECL(N, , );
X(Parameters);
X(Constructor);
X(Signature);

X(Declaration);
TALOS_XX_ANONYMOUS_NODES(X)
TALOS_XX_DECLARATION_NODES(X)
#undef X

#define X(N, ...) TALOS_MM_FORMAT_STMT(N, , , );
TALOS_XX_STATEMENT_NODES(X)
#undef X

#endif
