/* ///////////////////////////////////////////////////////////////////////
 * File:		arch.h		
 *
 * Created:		08.06.26					
 * Updated:		08.11.09	
 *
 * Brief:		Unix Architecture
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_UNIX_PLATFORM_H
#define EXTL_PLATFORM_UNIX_PLATFORM_H

#ifndef EXTL_PLATFORM_UNIX_CONFIG_H
#	error This file must be included of extl\platform\unix\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * UNIX platform detecting
 */
#ifdef EXTL_UNIX_PLATFORM_IS_INTEL
#	undef EXTL_UNIX_PLATFORM_IS_INTEL
#endif 

#ifdef EXTL_UNIX_PLATFORM_IS_POWERPC
#	undef EXTL_UNIX_PLATFORM_IS_POWERPC
#endif

#ifdef EXTL_UNIX_PLATFORM_IS_SPARC
#	undef EXTL_UNIX_PLATFORM_IS_SPARC
#endif

#ifdef EXTL_UNIX_PLATFORM_IS_UNKNOWN
#	undef EXTL_UNIX_PLATFORM_IS_UNKNOWN
#endif 

#if defined(__i386__) || \
    defined(__i386) || \
    defined(_M_IX86)
#	define EXTL_UNIX_PLATFORM_IS_INTEL
#elif defined(__ppc__) || \
      defined(__ppc) || \
      defined(__POWERPC__)
#	define EXTL_UNIX_PLATFORM_IS_POWERPC
#elif defined(__sparc__)
#	define EXTL_UNIX_PLATFORM_IS_SPARC
#else 
#	define EXTL_UNIX_PLATFORM_IS_UNKNOWN
#endif 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_UNIX_PLATFORM_H */
/* //////////////////////////////////////////////////////////////////// */

