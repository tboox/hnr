/* ///////////////////////////////////////////////////////////////////////
 * File:		is_obj.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_obj traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_OBJ_H
#define EXTL_TYPE_TRAITS_IS_OBJ_H

#ifndef EXTL_TYPE_TRAITS_IS_OBJ_SUPPORT
#	error extl::is_obj is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"
#include "is_ref.h"
#include "is_void.h"

#ifdef EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT
#	include "is_func.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_OBJ(type)			EXTL_MUST_BE_(is_obj, type)
#define EXTL_MUST_BE_CV_OBJ(type)		EXTL_MUST_BE_CV_(is_obj, type)

#define EXTL_MUST_NOT_BE_OBJ(type)		EXTL_MUST_NOT_BE_(is_obj, type)
#define EXTL_MUST_NOT_BE_CV_OBJ(type)	EXTL_MUST_NOT_BE_CV_(is_obj, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
#	if defined(EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT) && \
			!defined(EXTL_COMPILER_IS_BORLAND)
	EXTL_BOOL_TRAIT_DEF_1(is_obj, (op_and<
										(op_not< (is_ref<T>::value) >::value),
										(op_not< (is_void<T>::value) >::value),
										(op_not< (is_func<T>::value) >::value)
										>::value))
#	else
	EXTL_BOOL_TRAIT_DEF_1(is_obj, (op_and<
										(op_not< (is_ref<T>::value) >::value),
										(op_not< (is_void<T>::value) >::value)
										>::value))
#	endif

	
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_obj_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_OBJ_H */
/* //////////////////////////////////////////////////////////////////// */
