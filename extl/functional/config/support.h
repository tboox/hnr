/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Functional Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_FUNCTIONAL_CONFIG_SUPPORT_H
#define EXTL_FUNCTIONAL_CONFIG_SUPPORT_H

#ifndef EXTL_FUNCTIONAL_CONFIG_H
#	error This file must be included of extl\functional\config\config.h
#endif

#ifndef EXTL_TYPE_CONFIG_H
#	include "../type/config/config.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* func_ptr support */
#ifdef EXTL_FUNCTIONAL_FUNC_PTR_SUPPORT
#	undef EXTL_FUNCTIONAL_FUNC_PTR_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_SUPPORT) && \
		defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT)
#	define EXTL_FUNCTIONAL_FUNC_PTR_SUPPORT
#endif

/* mem_func_ptr support */
#ifdef EXTL_FUNCTIONAL_MEM_FUNC_PTR_SUPPORT
#	undef EXTL_FUNCTIONAL_MEM_FUNC_PTR_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_SUPPORT) && \
		defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT)
#	define EXTL_FUNCTIONAL_MEM_FUNC_PTR_SUPPORT
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_FUNCTIONAL_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
