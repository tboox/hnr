/* ///////////////////////////////////////////////////////////////////////
 * File:		is_fundamental.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_fundamental traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_FUNDAMENTAL_H
#define EXTL_TYPE_TRAITS_IS_FUNDAMENTAL_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_arithmetic.h"
#include "is_void.h"
#include "logical_op.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_FUNDAMENTAL(type)			EXTL_MUST_BE_(is_fundamental, type)
#define EXTL_MUST_BE_CV_FUNDAMENTAL(type)		EXTL_MUST_BE_CV_(is_fundamental, type)

#define EXTL_MUST_NOT_BE_FUNDAMENTAL(type)		EXTL_MUST_NOT_BE_(is_fundamental, type)
#define EXTL_MUST_NOT_BE_CV_FUNDAMENTAL(type)	EXTL_MUST_NOT_BE_CV_(is_fundamental, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(is_fundamental, (op_or< (is_arithmetic<T>::value), (is_void<T>::value),
						EXTL_OP_OR_DEF_ARG_2 >::value))

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_fundamental_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_FUNDAMENTAL_H */
/* //////////////////////////////////////////////////////////////////// */
