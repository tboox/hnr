/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Type Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_CONFIG_SUPPORT_H
#define EXTL_TYPE_CONFIG_SUPPORT_H

#ifndef EXTL_TYPE_CONFIG_H
#	error This file must be included of extl\type\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* non_type_wrap support */
#ifdef EXTL_NON_TYPE_WRAP_SUPPORT
#	undef EXTL_NON_TYPE_WRAP_SUPPORT
#endif

#ifdef EXTL_TEMPLATE_TYPENAME_T_T_N_SUPPORT
#	define EXTL_NON_TYPE_WRAP_SUPPORT
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
