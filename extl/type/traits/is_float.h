/* ///////////////////////////////////////////////////////////////////////
 * File:		is_float.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_float traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_FLOAT_H
#define EXTL_TYPE_TRAITS_IS_FLOAT_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_FLOAT(type)		EXTL_MUST_BE_(is_float, type)
#define EXTL_MUST_BE_CV_FLOAT(type)		EXTL_MUST_BE_CV_(is_float, type)

#define EXTL_MUST_NOT_BE_FLOAT(type)	EXTL_MUST_NOT_BE_(is_float, type)
#define EXTL_MUST_NOT_BE_CV_FLOAT(type)	EXTL_MUST_NOT_BE_CV_(is_float, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(is_float, e_false_v)

EXTL_BOOL_TRAIT_CV_SPEC_1(is_float, float, e_true_v)
EXTL_BOOL_TRAIT_CV_SPEC_1(is_float, double, e_true_v)
EXTL_BOOL_TRAIT_CV_SPEC_1(is_float, long double, e_true_v)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_float_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_FLOAT_H */
/* //////////////////////////////////////////////////////////////////// */
