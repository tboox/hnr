/* ///////////////////////////////////////////////////////////////////////
 * File:		is_scalar.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_scalar traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_SCALAR_H
#define EXTL_TYPE_TRAITS_IS_SCALAR_H

#ifndef EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#	error extl::is_scalar is not supported by current compiler. 
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_arithmetic.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#	include "is_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#	include "is_mem_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ENUM_SUPPORT
#	include "is_enum.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_SCALAR(type)			EXTL_MUST_BE_(is_scalar, type)
#define EXTL_MUST_BE_CV_SCALAR(type)		EXTL_MUST_BE_CV_(is_scalar, type)

#define EXTL_MUST_NOT_BE_SCALAR(type)		EXTL_MUST_NOT_BE_(is_scalar, type)
#define EXTL_MUST_NOT_BE_CV_SCALAR(type)	EXTL_MUST_NOT_BE_CV_(is_scalar, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#ifdef EXTL_TYPE_TRAITS_IS_ENUM_SUPPORT
EXTL_BOOL_TRAIT_DEF_1(is_scalar, (op_or	<	(is_arithmetic<T>::value)
										,	(is_ptr<T>::value)
										,	(is_mem_ptr<T>::value)
										,	(is_enum<T>::value)
										>::value))
#else
EXTL_BOOL_TRAIT_DEF_1(is_scalar, (op_or	<	(is_arithmetic<T>::value)
										,	(is_ptr<T>::value)
										,	(is_mem_ptr<T>::value)
										>::value))
#endif

	EXTL_BOOL_TRAIT_SPEC_1(is_scalar, void, e_false_v)
#	ifdef EXTL_CV_VOID_SPEC_SUPPORT	
	EXTL_BOOL_TRAIT_SPEC_1(is_scalar, void const, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_scalar, void volatile, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_scalar, void const volatile, e_false_v)
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_scalar_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_SCALAR_H */
/* //////////////////////////////////////////////////////////////////// */
