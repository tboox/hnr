/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Container Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_CONFIG_SUPPORT_H
#define EXTL_CONTAINER_CONFIG_SUPPORT_H

#ifndef EXTL_CONTAINER_CONFIG_H
#	error This file must be included of extl\container\config\config.h
#endif

#ifndef EXTL_TYPE_CONFIG_H
#	include "../type/config/config.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* tuple2 support */
#ifdef EXTL_CONTAINER_TUPLE2_SUPPORT
#	undef EXTL_CONTAINER_TUPLE2_SUPPORT
#endif

#ifdef EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#	define EXTL_CONTAINER_TUPLE2_SUPPORT
#endif

/* tuple support */
#ifdef EXTL_CONTAINER_TUPLE_SUPPORT
#	undef EXTL_CONTAINER_TUPLE_SUPPORT
#endif

#if defined(EXTL_0x_VARIADIC_TEMPLATE_SUPPORT) || \
		(defined(EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT) /* Watcom */ && \
			!defined(EXTL_COMPILER_IS_VECTORC) && \
				EXTL_WORKAROUND_BORLAND(!=, 0x551)) // Could not find a match for tuple<>::get<N>() when N >= 2
#	define EXTL_CONTAINER_TUPLE_SUPPORT
#endif

/* fixed_marray support */
#ifdef EXTL_CONTAINER_FIXED_MARRAY_SUPPORT
#	undef EXTL_CONTAINER_FIXED_MARRAY_SUPPORT
#endif

#if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT)  
#	define EXTL_CONTAINER_FIXED_MARRAY_SUPPORT
#endif

/* basic_net support */
#ifdef EXTL_CONTAINER_NET_SUPPORT
#	undef EXTL_CONTAINER_NET_SUPPORT
#endif

#if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT)  
#	define EXTL_CONTAINER_NET_SUPPORT
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
