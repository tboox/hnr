/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Function Optimization Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_GA_FOPTI_CONFIG_SUPPORT_H
#define EXTL_INTELLIGENCE_GA_FOPTI_CONFIG_SUPPORT_H

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_CONFIG_H
#	error This file must be included of extl\fopti\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
/* fopti_func_traits support */
#ifdef EXTL_FOPTI_FUNC_TRAITS_SUPPORT
#	undef EXTL_FOPTI_FUNC_TRAITS_SUPPORT
#endif

#if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT)
#	define EXTL_FOPTI_FUNC_TRAITS_SUPPORT
#endif

/* fopti_ga support */
#ifdef EXTL_FOPTI_GA_SUPPORT
#	undef EXTL_FOPTI_GA_SUPPORT
#endif

#if defined(EXTL_FOPTI_FUNC_TRAITS_SUPPORT) && \
		defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT) && \
			defined(EXTL_TEMPLATE_NON_TYPE_DEFAULT_PARAM_DEPENDENT_SUPPORT)
#	define EXTL_FOPTI_GA_SUPPORT
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
