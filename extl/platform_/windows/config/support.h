/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.06.26					
 * Updated:		08.11.09	
 *
 * Brief:		compiler support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WINDOWS_SUPPORT_H
#define EXTL_PLATFORM_WINDOWS_SUPPORT_H

#ifndef EXTL_PLATFORM_WINDOWS_CONFIG_H
#	error This file must be included of extl\platform\windows\config\config.h
#endif

#if !defined(WIN32) && \
		!defined(_WIN32)
#	error The Windows cannot use Win API.
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include <windows.h>

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility 
 */
#ifndef EXTL_CONFIG_COMPILER_H
#	error This file must be depended on extl\config\compiler\config.h
#endif

#ifdef EXTL_WINDOWS_NO_SUPPORT
#	undef EXTL_WINDOWS_NO_SUPPORT
#endif

/* compiler support */
#if defined(EXTL_PLATFORM_IS_WINDOWS)

#	if defined(EXTL_COMPILER_IS_BORLAND)
#		if __BORLANDC__ < 0x0550
#			define EXTL_WINDOWS_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_GCC)
#		if __GNUC__ < 3
#			define EXTL_WINDOWS_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_INTEL)
#		if (__INTEL_COMPILER < 600)
#			define EXTL_WINDOWS_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_MSVC)
#		if _MSC_VER < 1020
#			define EXTL_WINDOWS_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_WATCOM)
#		if (__WATCOMC__ < 1200)
#			define EXTL_WINDOWS_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_DMC)
#		if (__DMC__ < 0x0826)
#			define EXTL_WINDOWS_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_VECTORC)

#	else
#		error Currently only Borland C++, GNU C++, Intel C/C++, Visual C++ and Watcom compilers are supported by the Win.
#	endif 

#else
#	error This file is not supported by windows platform.
#endif


/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */

