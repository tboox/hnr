/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.02.02				
 * Updated:		08.06.26	
 *
 * Brief: Unix platform configuration
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_UNIX_CONFIG_H
#define EXTL_PLATFORM_UNIX_CONFIG_H

#ifndef EXTL_PLATFORM_CONFIG_H
#	error This file must be included of platform\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility 
 */
#ifndef EXTL_CONFIG_COMPILER_H
#	error This file must be depended on compiler\config.h
#endif

#ifdef EXTL_UNIX_NO_SUPPORT
#	undef EXTL_UNIX_NO_SUPPORT
#endif

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
#	error This file is supported by Unix platform.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Architecture
 */
#ifdef EXTL_UNIX_ARCH_IS_INTEL
#	undef EXTL_UNIX_ARCH_IS_INTEL
#endif 
#ifdef EXTL_UNIX_ARCH_IS_POWERPC
#	undef EXTL_UNIX_ARCH_IS_POWERPC
#endif
#ifdef EXTL_UNIX_ARCH_IS_SPARC
#	undef EXTL_UNIX_ARCH_IS_SPARC
#endif
#ifdef EXTL_UNIX_ARCH_IS_UNKNOWN
#	undef EXTL_UNIX_ARCH_IS_UNKNOWN
#endif 

#if defined(__i386__) || \
    defined(__i386) || \
    defined(_M_IX86)
#	define EXTL_UNIX_ARCH_IS_INTEL
#elif defined(__ppc__) || \
      defined(__ppc) || \
      defined(__POWERPC__)
#	define EXTL_UNIX_ARCH_IS_POWERPC
#elif defined(__sparc__)
#	define EXTL_UNIX_ARCH_IS_SPARC
#else 
#	define EXTL_UNIX_ARCH_IS_UNKNOWN
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * operating system aggreement
 */
#ifdef EXTL_UNIX_OSFAMILY_IS_BSD
#	undef EXTL_UNIX_OSFAMILY_IS_BSD
#endif 
#ifdef EXTL_UNIX_OSFAMILY_IS_SVR4
#	undef EXTL_UNIX_OSFAMILY_IS_SVR4
#endif 


#if defined(__FreeBSD__) || \
    defined(__NetBSD__) || \
    defined(__OpenBSD__) || \
    defined(__bsdi__) || \
    defined(_SYSTYPE_BSD)
#	define EXTL_UNIX_OSFAMILY_IS_BSD
#endif 

#if defined(__sysv__) || \
    defined(__SVR4) || \
    defined(__svr4__) || \
    defined(_SYSTYPE_SVR4)
#	define EXTL_UNIX_OSFAMILY_IS_SVR4
#endif

/* ///////////////////////////////////////////////////////////////////////
 * UNIX platform detecting
 */
#ifdef EXTL_UNIX_PLATFORM_IS_APPLE
#	undef EXTL_UNIX_PLATFORM_IS_APPLE
#endif 
#ifdef EXTL_UNIX_PLATFORM_IS_AIX
#	undef EXTL_UNIX_PLATFORM_IS_AIX
#endif 
#ifdef EXTL_UNIX_PLATFORM_IS_FREEBSD
#	undef EXTL_UNIX_PLATFORM_IS_FREEBSD
#endif 
#ifdef EXTL_UNIX_PLATFORM_IS_HPUX
#	undef EXTL_UNIX_PLATFORM_IS_HPUX
#endif 
#ifdef EXTL_UNIX_PLATFORM_IS_LINUX
#	undef EXTL_UNIX_PLATFORM_IS_LINUX
#endif 
#ifdef EXTL_UNIX_PLATFORM_IS_MACOSX
#	undef EXTL_UNIX_PLATFORM_IS_MACOSX
#endif 
#ifdef EXTL_UNIX_PLATFORM_IS_NETBSD
#	undef EXTL_UNIX_PLATFORM_IS_NETBSD
#endif
#ifdef EXTL_UNIX_PLATFORM_IS_OPENBSD
#	undef EXTL_UNIX_PLATFORM_IS_OPENBSD
#endif 
#ifdef EXTL_UNIX_PLATFORM_IS_SOLARIS
#	undef EXTL_UNIX_PLATFORM_IS_SOLARIS
#endif
#ifdef EXTL_UNIX_PLATFORM_IS_FREEBSD
#	undef EXTL_UNIX_PLATFORM_IS_FREEBSD
#endif 
#ifdef EXTL_UNIX_PLATFORM_IS_UNKNOWN
#	undef EXTL_UNIX_PLATFORM_IS_UNKNOWN
#endif 

#if defined(__APPLE__) || \
    defined(__MACOSX__)
#	define EXTL_UNIX_PLATFORM_IS_APPLE
	define EXTL_UNIX_PLATFORM_IS_MACOSX
#elif defined(_AIX)
#	define EXTL_UNIX_PLATFORM_IS_AIX
#elif defined(__FreeBSD__)
#	define EXTL_UNIX_PLATFORM_IS_FREEBSD
#elif defined(hpux) || \
      defined(_hpux)
#	define EXTL_UNIX_PLATFORM_IS_HPUX
#elif defined(__linux__) || \
      defined(__linux) || \
      defined(linux)
#	define EXTL_UNIX_PLATFORM_IS_LINUX
#elif defined(__NetBSD__)
#	define EXTL_UNIX_PLATFORM_IS_NETBSD
#elif defined(__OpenBSD__)
#	define EXTL_UNIX_PLATFORM_IS_OPENBSD
#elif defined(sun) || \
      defined(__sun)
#	if defined(EXTL_UNIX_OSFAMILY_IS_SVR4)
#		define EXTL_UNIX_PLATFORM_IS_SOLARIS
#	else
#		define EXTL_UNIX_PLATFORM_IS_SUNOS
#	endif 
#else 
#	define EXTL_UNIX_PLATFORM_IS_UNKNOWN
#endif 


/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_UNIX_CONFIG_H */
/* //////////////////////////////////////////////////////////////////// */

