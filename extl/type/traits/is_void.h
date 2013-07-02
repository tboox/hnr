/* ///////////////////////////////////////////////////////////////////////
 * File:		is_void.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_void traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_VOID_H
#define EXTL_TYPE_TRAITS_IS_VOID_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_VOID(type)			EXTL_MUST_BE_(is_void, type)
#define EXTL_MUST_BE_CV_VOID(type)		EXTL_MUST_BE_CV_(is_void, type)

#define EXTL_MUST_NOT_BE_VOID(type)		EXTL_MUST_NOT_BE_(is_void, type)
#define EXTL_MUST_NOT_BE_CV_VOID(type)	EXTL_MUST_NOT_BE_CV_(is_void, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(is_void, e_false_v)
EXTL_BOOL_TRAIT_SPEC_1(is_void, void, e_true_v)

#	ifdef EXTL_CV_VOID_SPEC_SUPPORT	
	EXTL_BOOL_TRAIT_SPEC_1(is_void, void const, e_true_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_void, void volatile, e_true_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_void, void const volatile, e_true_v)
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_void_test.h"
#	endif
#endif	/* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_VOID_H */
/* //////////////////////////////////////////////////////////////////// */
