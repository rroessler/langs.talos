#ifndef _XTDLIB_ENUM_CLASS_HPP
#define _XTDLIB_ENUM_CLASS_HPP

//  MACROS  //

#define $_XX_ENUM_COUNT(...) 1 +
#define $_XX_ENUM_INFER(N, ...) N,
#define $_XX_ENUM_VALUE(N, V, ...) N = V,
#define $_XX_ENUM_CLASS(T, U, L, ...) enum class T : U { L($_XX_ENUM_INFER) __VA_ARGS__ }

#endif
