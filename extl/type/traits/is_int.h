/* ///////////////////////////////////////////////////////////////////////
 * File:		is_int.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_int traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_INT_H
#define EXTL_TYPE_TRAITS_IS_INT_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_INT(type)			EXTL_MUST_BE_(is_int, type)
#define EXTL_MUST_BE_CV_INT(type)		EXTL_MUST_BE_CV_(is_int, type)

#define EXTL_MUST_NOT_BE_INT(type)		EXTL_MUST_NOT_BE_(is_int, type)
#define EXTL_MUST_NOT_BE_CV_INT(type)	EXTL_MUST_NOT_BE_CV_(is_int, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(is_int, e_false_v)

EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned char, e_true_v)
EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned short, e_true_v)
EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned int, e_true_v)
EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned long, e_true_v)

EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed char, e_true_v)
EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed short, e_true_v)
EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed int, e_true_v)
EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed long, e_true_v)

EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, char, e_true_v)

#	ifdef EXTL_NATIVE_BOOL_SUPPORT
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, bool, e_true_v)
#	endif

#	ifdef EXTL_NATIVE_WCHAR_T_SUPPORT
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, wchar_t, e_true_v)
#	endif

#	ifdef EXTL_08BIT_INT_IS___int8
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned __int8, e_true_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed __int8, e_true_v)
#	endif

#	ifdef EXTL_16BIT_INT_IS___int16
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned __int16, e_true_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed __int16, e_true_v)
#	endif

#	ifdef EXTL_32BIT_INT_IS___int32
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned __int32, e_true_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed __int32, e_true_v)
#	endif

#	ifdef EXTL_64BIT_INT_IS___int64
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned __int64, e_true_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed __int64, e_true_v)
#	endif

#	ifdef EXTL_64BIT_INT_IS_long_long
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, unsigned long long, e_true_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_int, signed long long, e_true_v)
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_int_test.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_INT_H */
/* //////////////////////////////////////////////////////////////////// */
