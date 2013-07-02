/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Windows Counter Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_COUNTER_CONFIG_SUPPORT_H
#define EXTL_PLATFORM_WINDOWS_COUNTER_CONFIG_SUPPORT_H

#ifndef EXTL_PLATFORM_WINDOWS_CONFIG_H
#	error This file must be included of extl\platform\windows\config\config.h
#endif

#ifndef EXTL_PLATFORM_WINDOWS_CONFIG_SUB_H
#	error This file must be included of extl\platform\windows\config\sub_config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
/* rdtsc_counter support */
#ifdef EXTL_WINDOWS_COUNTER_RDTSC_COUNTER_SUPPORT
#	undef EXTL_WINDOWS_COUNTER_RDTSC_COUNTER_SUPPORT
#endif

#if defined(EXTL_INLINE_ASM_SUPPORT) && \
		!defined(EXTL_COMPILER_IS_WATCOM)
#	define EXTL_WINDOWS_COUNTER_RDTSC_COUNTER_SUPPORT
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_COUNTER_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
