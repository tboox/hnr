/* ///////////////////////////////////////////////////////////////////////
 * File:		is_compound.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09
 *
 * Brief: is_compound traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_COMPOUND_H
#define EXTL_TYPE_TRAITS_IS_COMPOUND_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"
#include "is_fundamental.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_COMPOUND(type)			EXTL_MUST_BE_(is_compound, type)
#define EXTL_MUST_BE_CV_COMPOUND(type)		EXTL_MUST_BE_CV_(is_compound, type)

#define EXTL_MUST_NOT_BE_COMPOUND(type)		EXTL_MUST_NOT_BE_(is_compound, type)
#define EXTL_MUST_NOT_BE_CV_COMPOUND(type)	EXTL_MUST_NOT_BE_CV_(is_compound, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(is_compound, op_not< (is_fundamental< T >::value) >::value)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_compound_test.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_COMPOUND_H */
/* //////////////////////////////////////////////////////////////////// */
