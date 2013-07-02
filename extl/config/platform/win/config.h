/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.02.02				
 * Updated:		08.06.26	
 *
 * Brief: Win32 platform configuration
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONFIG_PLATFORM_WIN_H
#define EXTL_CONFIG_PLATFORM_WIN_H

#ifndef EXTL_CONFIG_PLATFORM_H
#	error This file must be included of platform\config.h
#endif

#if !defined(WIN32) && \
		!defined(_WIN32)
#	error The Win cannot use Win API.
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include <windows.h>

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility 
 */
#ifndef EXTL_CONFIG_COMPILER_H
#	error This file must be depended on compiler\config.h
#endif

#ifdef EXTL_WIN_NO_SUPPORT
#	undef EXTL_WIN_NO_SUPPORT
#endif

/* Wind32 */
#if defined(EXTL_PLATFORM_IS_WIN)

#	if defined(EXTL_COMPILER_IS_BORLAND)
#		if __BORLANDC__ < 0x0550
#			define EXTL_WIN_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_GCC)
#		if __GNUC__ < 3
#			define EXTL_WIN_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_INTEL)
#		if (__INTEL_COMPILER < 600)
#			define EXTL_WIN_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_MSVC)
#		if _MSC_VER < 1020
#			define EXTL_WIN_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_WATCOM)
#		if (__WATCOMC__ < 1200)
#			define EXTL_WIN_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_DMC)
#		if (__DMC__ < 0x0826)
#			define EXTL_WIN_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_VECTORC)

#	else
#		error Currently only Borland C++, GNU C++, Intel C/C++, Visual C++ and Watcom compilers are supported by the Win.
#	endif 

#else
#	error This file is supported by Win platform.
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_PLATFORM_WIN_H */
/* //////////////////////////////////////////////////////////////////// */

