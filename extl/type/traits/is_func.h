/* ///////////////////////////////////////////////////////////////////////
 * File:		is_func.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_func traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_FUNC_H
#define EXTL_TYPE_TRAITS_IS_FUNC_H

#ifndef EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT
#	error extl::is_func is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_FUNC_PTR_SUPPORT
#	include "is_func_ptr.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_FUNC(type)			EXTL_MUST_BE_(is_func, type)
#define EXTL_MUST_BE_CV_FUNC(type)		EXTL_MUST_BE_CV_(is_func, type)

#define EXTL_MUST_NOT_BE_FUNC(type)		EXTL_MUST_NOT_BE_(is_func, type)
#define EXTL_MUST_NOT_BE_CV_FUNC(type)	EXTL_MUST_NOT_BE_CV_(is_func, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
	EXTL_BOOL_TRAIT_DEF_1(is_func, is_func_ptr<T*>::value)
	/* exclude reference type */
	EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_func, T&, e_false_v)
#	else	

	char EXTL_CDECL is_func_helper1(...);
	template <typename_param_k T> 
	T(* is_func_helper1(type_wrap<T>))[1];

	yes_type EXTL_CDECL is_func_helper2(...);
	template <typename_param_k T> 
	no_type is_func_helper2(T (*)[1]); /* exclude function type */

	EXTL_BOOL_TRAIT_DEF_1(is_func, sizeof(is_func_helper2(is_func_helper1(type_wrap<T>()))) == sizeof(yes_type))

	EXTL_BOOL_TRAIT_SPEC_1(is_func, void, e_false_v)
#		ifdef EXTL_CV_VOID_SPEC_SUPPORT	
		EXTL_BOOL_TRAIT_SPEC_1(is_func, void const, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_func, void volatile, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_func, void const volatile, e_false_v)
#		endif

#	endif 

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_func_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_FUNC_H */
/* //////////////////////////////////////////////////////////////////// */
