#ifndef _XTDLIB_PORTABLE_WINDOWS_HPP
#define _XTDLIB_PORTABLE_WINDOWS_HPP

/// Library Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_WINDOWS

// There are some ordering issues internally in the SDK; we need to ensure
// stdio.h is included prior to including direct.h and io.h with internal names
// disabled to ensure all of the normal names get declared properly.
#include <stdio.h>

//  MACROS  //

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef NOGDI
#define NOGDI
#endif

#ifndef __STDC__
/* nolint */
#define __STDC__ 1
#pragma push_macro("_CRT_DECLARE_NONSTDC_NAMES")
#ifdef _CRT_DECLARE_NONSTDC_NAMES
#undef _CRT_DECLARE_NONSTDC_NAMES
#endif
#pragma push_macro("_CRT_INTERNAL_NONSTDC_NAMES")
#undef _CRT_INTERNAL_NONSTDC_NAMES
#include <direct.h>
#include <io.h>
#undef __STDC__
#pragma pop_macro("_CRT_INTERNAL_NONSTDC_NAMES")
#pragma pop_macro("_CRT_DECLARE_NONSTDC_NAMES")
#else
#include <direct.h>
#include <io.h>
#endif

#if defined(min) || defined(max)
#error "windows.h" needs to be included by this header, or else NOMINMAX needs to be defined before including it manually.
#endif

/// Platform Modules
#include <windows.h>

/// Library Modules
#include "xtdlib/portable/_defines/windows.def"

#endif
#endif
