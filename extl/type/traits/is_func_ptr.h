/* ///////////////////////////////////////////////////////////////////////
 * File:		is_func_ptr.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_func_ptr traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_FUNC_PTR_H
#define EXTL_TYPE_TRAITS_IS_FUNC_PTR_H

#ifndef EXTL_TYPE_TRAITS_IS_FUNC_PTR_SUPPORT
#	error extl::is_func_ptr is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "detail/is_func_ptr_tester.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_FUNC_PTR(type)			EXTL_MUST_BE_(is_func_ptr, type)
#define EXTL_MUST_BE_CV_FUNC_PTR(type)		EXTL_MUST_BE_CV_(is_func_ptr, type)

#define EXTL_MUST_NOT_BE_FUNC_PTR(type)		EXTL_MUST_NOT_BE_(is_func_ptr, type)
#define EXTL_MUST_NOT_BE_CV_FUNC_PTR(type)	EXTL_MUST_NOT_BE_CV_(is_func_ptr, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

template < typename_param_k T >
struct is_func_ptr_impl
{
	static T t;
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(EXTL_NS_DETAIL(is_func_ptr_tester)(t)) == sizeof(yes_type)));
};

EXTL_BOOL_TRAIT_DEF_1(is_func_ptr, is_func_ptr_impl<T>::value)

EXTL_BOOL_TRAIT_SPEC_1(is_func_ptr, void, e_false_v)
#	ifdef EXTL_CV_VOID_SPEC_SUPPORT	
	EXTL_BOOL_TRAIT_SPEC_1(is_func_ptr, void const, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_func_ptr, void volatile, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_func_ptr, void const volatile, e_false_v)
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_func_ptr_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_FUNC_PTR_H */
/* //////////////////////////////////////////////////////////////////// */
