/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Math Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MATH_CONFIG_SUPPORT_H
#define EXTL_MATH_CONFIG_SUPPORT_H

#ifndef EXTL_MATH_CONFIG_H
#	error This file must be included of extl\math\config\config.h
#endif

#ifndef EXTL_TYPE_CONFIG_H
#	include "../type/config/config.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* non_type_wrap support */
#ifdef EXTL_MATH_EXPR_VVECTOR_SUPPORT
#	undef EXTL_MATH_EXPR_VVECTOR_SUPPORT
#endif

#ifdef EXTL_MEMBER_TEMPLATE_FUNCTION_SUPPORT
#	define EXTL_MATH_EXPR_VVECTOR_SUPPORT
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
