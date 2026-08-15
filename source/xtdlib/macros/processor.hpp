#ifndef _XTDLIB_MACROS_PROCESSOR_HPP
#define _XTDLIB_MACROS_PROCESSOR_HPP

//  MACROS  //

#define $_PP_IGN(E) ((void)(E))
#define $_PP_NOOP() $_PP_IGN(0)

#define $_PP_COMMA ,
#define $_PP_VOPT_ARGS(A, B, C, ...) C
#define $_PP_VOPT_IMPL(...) $_PP_VOPT_ARGS(__VA_OPT__(, ), true, false, )

#if $_PP_VOPT_IMPL(?)
#define $_PP_VARGS(...) __VA_OPT__(, ) __VA_ARGS__
#else
#define $_PP_VARGS(...) , ##__VA_ARGS__
#endif

#define $_PP_SCOPE(...)
#define $_PP_BLOCK(...)        \
  do __VA_ARGS__ while (false)

#define $_PP_STRINGIFY_IMPL(X) #X
#define $_PP_STRINGIFY(X) $_PP_STRINGIFY_IMPL(X)

#define $_PP_CONCAT_IMPL(A, B) A##B
#define $_PP_CONCAT(A, B) $_PP_CONCAT_IMPL(A, B)

#ifdef NDEBUG
#define $_PP_NDEBUG 1
#else
#define $_PP_NDEBUG 0
#endif

#if defined(__COUNTER__)
#define $_PP_UNIQUE(NAME) $_PP_CONCAT(NAME##_, __COUNTER__)
#else
#define $_PP_UNIQUE(NAME) $_PP_CONCAT(NAME##_, __LINE__)
#endif

#endif
