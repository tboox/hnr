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

#ifndef EXTL_PLATFORM_UNIX_SUPPORT_H
#define EXTL_PLATFORM_UNIX_SUPPORT_H

#ifndef EXTL_PLATFORM_UNIX_CONFIG_H
#	error This file must be included of extl\platform\unix\config\config.h
#endif

#ifdef EXTL_UNIX_NO_SUPPORT
#	undef EXTL_UNIX_NO_SUPPORT
#endif

/* compiler support */
#if defined(EXTL_PLATFORM_IS_UNIX)

#	if defined(EXTL_COMPILER_IS_GCC)
#		if __GNUC__ < 2 || \
			 (  __GNUC__ == 2 && \
				__GNUC_MINOR__ < 95)
#			define EXTL_UNIX_NO_SUPPORT
#		endif 

#	elif defined(EXTL_COMPILER_IS_INTEL)
#		if (__INTEL_COMPILER < 700)
#			define EXTL_UNIX_NO_SUPPORT
#		endif 

#	else
#		error Currently only GNU C++, Intel C/C++ compilers are supported by the Unix.
#	endif

#else
#	error This file is not supported by unix platform.
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_UNIX_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */

