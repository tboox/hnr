/* ///////////////////////////////////////////////////////////////////////
 * File:		is_arithmetic.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09
 *
 * Brief: is_arithmetic traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_ARITHMETIC_H
#define EXTL_TYPE_TRAITS_IS_ARITHMETIC_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"
#include "is_float.h"
#include "is_int.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_ARITHMETIC(type)		EXTL_MUST_BE_(is_arithmetic, type)
#define EXTL_MUST_BE_CV_ARITHMETIC(type)	EXTL_MUST_BE_CV_(is_arithmetic, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

template< typename_param_k T >
struct is_arithmetic_impl
{ 
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_or	<	is_int<T>::value
														,	is_float<T>::value 
														,	EXTL_OP_OR_DEF_ARG_2 
														>::value)); 
};

EXTL_BOOL_TRAIT_DEF_1(is_arithmetic, is_arithmetic_impl<T>::value)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_arithmetic_test.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_ARITHMETIC_H */
/* //////////////////////////////////////////////////////////////////// */
