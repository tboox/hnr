/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Utility Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_CONFIG_SUPPORT_H
#define EXTL_UTILITY_CONFIG_SUPPORT_H

#ifndef EXTL_UTILITY_CONFIG_H
#	error This file must be included of extl\utility\config\config.h
#endif

/*#ifndef EXTL_TYPE_CONFIG_H
#	include "../type/config/config.h"
#endif*/

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifdef EXTL_UTILITY_PROPERTIES_SUPPORT
#	undef EXTL_UTILITY_PROPERTIES_SUPPORT
#endif

#if defined(EXTL_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT) && \
		defined(EXTL_PROPERTY_SUPPORT)
#	define  EXTL_UTILITY_PROPERTIES_SUPPORT
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
