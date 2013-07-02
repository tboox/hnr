/* ///////////////////////////////////////////////////////////////////////
 * File:		os_family.h		
 *
 * Created:		08.06.26					
 * Updated:		08.11.09	
 *
 * Brief:		Unix Operating System Family
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_OS_FAMILY_UNIX_OS_FAMILY_H
#define EXTL_OS_FAMILY_UNIX_OS_FAMILY_H

#ifndef EXTL_PLATFORM_UNIX_CONFIG_H
#	error This file must be included of extl\platform\unix\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * operating system aggreement
 */
#ifdef EXTL_UNIX_OS_FAMILY_IS_BSD
#	undef EXTL_UNIX_OS_FAMILY_IS_BSD
#endif 
#ifdef EXTL_UNIX_OS_FAMILY_IS_SVR4
#	undef EXTL_UNIX_OS_FAMILY_IS_SVR4
#endif 


#if defined(__FreeBSD__) || \
    defined(__NetBSD__) || \
    defined(__OpenBSD__) || \
    defined(__bsdi__) || \
    defined(_SYSTYPE_BSD)
#	define EXTL_UNIX_OS_FAMILY_IS_BSD
#endif 

#if defined(__sysv__) || \
    defined(__SVR4) || \
    defined(__svr4__) || \
    defined(_SYSTYPE_SVR4)
#	define EXTL_UNIX_OS_FAMILY_IS_SVR4
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_OS_FAMILY_UNIX_OS_FAMILY_H */
/* //////////////////////////////////////////////////////////////////// */

