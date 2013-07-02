/* ///////////////////////////////////////////////////////////////////////
 * File:		is_array.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09
 *
 * Brief: is_array traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_ARRAY_H
#define EXTL_TYPE_TRAITS_IS_ARRAY_H

#ifndef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	error extl::is_array is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"

#ifndef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT // for VC6.0 ...
#	ifdef EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT
#		include "is_func.h"
#	endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_ARRAY(type)		EXTL_MUST_BE_(is_array, type)
#define EXTL_MUST_BE_CV_ARRAY(type)		EXTL_MUST_BE_CV_(is_array, type)

#define EXTL_MUST_NOT_BE_ARRAY(type)	EXTL_MUST_NOT_BE_(is_array, type)
#define EXTL_MUST_NOT_BE_CV_ARRAY(type)	EXTL_MUST_NOT_BE_CV_(is_array, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

	EXTL_BOOL_TRAIT_DEF_1(is_array, e_false_v)

	EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, is_array, T[N], e_true_v)
	EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, is_array, T const[N], e_true_v)
	EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, is_array, T volatile[N], e_true_v)
	EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, is_array, T const volatile[N], e_true_v)

#		if !defined(EXTL_COMPILER_IS_BORLAND) && \
				!defined(EXTL_COMPILER_IS_DMC) && \
					!defined(EXTL_COMPILER_IS_VECTORC)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_array, T[], e_true_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_array, T const[], e_true_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_array, T volatile[], e_true_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_array, T const volatile[], e_true_v)
#		endif

#	else	/* !defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) */

	char EXTL_CDECL is_array_helper1(...);
	template< typename_param_k T > 
	T(* is_array_helper1(type_wrap<T>) )(type_wrap<T>);
	
	yes_type EXTL_CDECL is_array_helper2(...);
	template< typename_param_k T> 
	no_type is_array_helper2(T(*)(type_wrap<T>)); // note: cannot exclude function type 

	//EXTL_BOOL_TRAIT_DEF_1(is_array, sizeof(is_array_helper2(is_array_helper1(type_wrap<T>()))) == sizeof(yes_type))
	EXTL_BOOL_TRAIT_DEF_1(is_array, (op_and	<	(sizeof(is_array_helper2(is_array_helper1(type_wrap<T>()))) == sizeof(yes_type))
											,	(op_not<(is_func<T>::value)>::value) // exclude function type 
											>::value))
	
	EXTL_BOOL_TRAIT_SPEC_1(is_array, void, e_false_v)
#		ifdef EXTL_CV_VOID_SPEC_SUPPORT	
		EXTL_BOOL_TRAIT_SPEC_1(is_array, void const, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_array, void volatile, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_array, void const volatile, e_false_v)
#		endif

#	endif	/* EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_array_test.h"
#	endif
#endif	

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_ARRAY_H */
/* //////////////////////////////////////////////////////////////////// */
