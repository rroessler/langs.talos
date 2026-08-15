#ifndef _TALOS_PARSER_MACROS_IPP
#define _TALOS_PARSER_MACROS_IPP

/// Talos Includes
#include "talos/parser/dispatch.hpp"

//  MACROS  //

#define TALOS_MM_PARSE_FWD(N, R, T, ...)                                                      \
  template <> Talos::Syntax::R *Talos::Parser::Dispatch::m_##N<Talos::Syntax::T>(__VA_ARGS__)

#define TALOS_MM_PARSE_DECL(T, P, ...) TALOS_MM_PARSE_FWD(declaration, T, T, Stream *P)
#define TALOS_MM_PARSE_STMT(T, P, ...) TALOS_MM_PARSE_FWD(statement, T, T, Stream *P)
#define TALOS_MM_PARSE_HINT(T, P, ...) TALOS_MM_PARSE_FWD(annotation, T, T, Stream *P)
#define TALOS_MM_PARSE_PREFIX(T, P, A, ...) TALOS_MM_PARSE_FWD(prefix, Expression, T, Stream *P, bool A)
#define TALOS_MM_PARSE_INFIX(T, P, E, A, ...)                                        \
  TALOS_MM_PARSE_FWD(infix, Expression, T, Stream *P, Syntax::Expression *E, bool A)

#endif
