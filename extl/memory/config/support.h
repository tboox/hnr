/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Memory Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MEMORY_CONFIG_SUPPORT_H
#define EXTL_MEMORY_CONFIG_SUPPORT_H

#ifndef EXTL_MEMORY_CONFIG_H
#	error This file must be included of extl\memory\config\config.h
#endif

#ifndef EXTL_TYPE_CONFIG_H
#	include "../type/config/config.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* rebind support */
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
#	undef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
#endif

#if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) && \
		!EXTL_WORKAROUND_MSVC(==, 1200) /* VC6.0: INTERNAL COMPILER ERROR */
#	define EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
#endif

/* exists _Charalloc method in the standard library*/
#ifdef EXTL_ALLOCATOR_CHARALLOC_METHOD
#	undef EXTL_ALLOCATOR_CHARALLOC_METHOD           
#endif

#if (defined(EXTL_COMPILER_IS_INTEL) || defined(EXTL_COMPILER_IS_MSVC)) && \
				(_MSC_VER >= 1100 &&  _MSC_VER < 1300)
#	define EXTL_ALLOCATOR_CHARALLOC_METHOD     
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
