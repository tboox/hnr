/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The MPL Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_CONFIG_SUPPORT_H
#define EXTL_MPL_CONFIG_SUPPORT_H

#ifndef EXTL_MPL_CONFIG_H
#	error This file must be included of extl\mpl\config\config.h
#endif

#ifndef EXTL_TYPE_CONFIG_H
#	include "../type/config/config.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* Mpl support */
#ifdef EXTL_MPL_SUPPORT
#	undef EXTL_MPL_SUPPORT
#endif

#if defined(__cplusplus) && \
	defined(EXTL_TEMPLATE_SUPPORT) && \
		defined(EXTL_TEMPLATE_SPEC_SUPPORT)
#	define EXTL_MPL_SUPPORT
#endif

/* mpl::if_ support */
#ifdef EXTL_MPL_IF_SUPPORT
#	undef EXTL_MPL_IF_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT)
#	define EXTL_MPL_IF_SUPPORT
#endif

/* mpl::sqrt support */
#ifdef EXTL_MPL_MATH_SQRT_SUPPORT
#	undef EXTL_MPL_MATH_SQRT_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_MPL_IF_SUPPORT)
#	define EXTL_MPL_MATH_SQRT_SUPPORT
#endif

/* mpl::pow support */
#ifdef EXTL_MPL_MATH_POW_SUPPORT
#	undef EXTL_MPL_MATH_POW_SUPPORT
#endif

#if defined(EXTL_MPL_IF_SUPPORT)
#	define EXTL_MPL_MATH_POW_SUPPORT
#endif

/* mpl::log support */
#ifdef EXTL_MPL_MATH_LOG_SUPPORT
#	undef EXTL_MPL_MATH_LOG_SUPPORT
#endif

#if defined(EXTL_MPL_IF_SUPPORT)
#	define EXTL_MPL_MATH_LOG_SUPPORT
#endif

/* mpl::pi support */
#ifdef EXTL_MPL_MATH_PI_SUPPORT
#	undef EXTL_MPL_MATH_PI_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_SPEC_WITHIN_TEMPLATE_CLASS_SUPPORT) && \
		defined(EXTL_MPL_MATH_POW_SUPPORT) && \
			!EXTL_WORKAROUND_DMC(==, 0x840)
#	define EXTL_MPL_MATH_PI_SUPPORT
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
