#ifndef _XTDLIB_PORTABLE_WINDOWS_HPP
#define _XTDLIB_PORTABLE_WINDOWS_HPP

/// Library Includes
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

//  UNDEFINES  //

// Defined in the GDI interface.
#ifdef ERROR
#undef ERROR
#endif

// Defined in winnt.h
#ifdef VOID
#undef VOID
#endif

// Defined in winnt.h
#ifdef DELETE
#undef DELETE
#endif

// Defined in minwindef.h
#ifdef IN
#undef IN
#endif

// Defined in minwindef.h
#ifdef CALLBACK
#undef CALLBACK
#endif

// Defined in minwindef.h
#ifdef TRUE
#undef TRUE
#endif

// Defined in minwindef.h
#ifdef FALSE
#undef FALSE
#endif

// Defined in minwindef.h
#ifdef OPTIONAL
#undef OPTIONAL
#endif

// Defined in winerror.h
#ifdef NO_ERROR
#undef NO_ERROR
#endif

// Defined in minwindef.h
#ifdef OUT
#undef OUT
#endif

// Defined in minwindef.h
#ifdef STRICT
#undef STRICT
#endif

// Defined in Winbase.h
#ifdef Yield
#undef Yield
#endif

// Defined in Winbase.h
#ifdef IGNORE
#undef IGNORE
#endif

// Defined in nb30.h
#ifdef REGISTERED
#undef REGISTERED
#endif

#endif

#endif
