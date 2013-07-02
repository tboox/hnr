/* ///////////////////////////////////////////////////////////////////////
 * File:		is_ref.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09
 *
 * Brief: is_ref traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_REF_H
#define EXTL_TYPE_TRAITS_IS_REF_H

#ifndef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	error extl::is_ref is not supported by current compiler.
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
#define EXTL_MUST_BE_REF(type)			EXTL_MUST_BE_(is_ref, type)
#define EXTL_MUST_BE_CV_REF(type)		EXTL_MUST_BE_CV_(is_ref, type)
#define EXTL_MUST_NOT_BE_REF(type)		EXTL_MUST_NOT_BE_(is_ref, type)
#define EXTL_MUST_NOT_BE_CV_REF(type)	EXTL_MUST_NOT_BE_CV_(is_ref, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

	EXTL_BOOL_TRAIT_DEF_1(is_ref, e_false_v)
	EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ref, T&, e_true_v)

#		if defined(EXTL_COMPILER_IS_BORLAND) && !defined(__COMO__) && (__BORLANDC__ < 0x600)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ref, T& const, e_true_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ref, T& volatile, e_true_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ref, T& const volatile, e_true_v)
#		endif

#		if defined(EXTL_COMPILER_IS_GCC) && (__GNUC__ < 3)
		// these allow us to work around illegally cv-qualified reference types
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ref, T const , is_ref<T>::value)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ref, T volatile , is_ref<T>::value)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ref, T const volatile , is_ref<T>::value)
		// However, the above specializations confuse gcc 2.96 unless we also
		// supply these specializations for array types
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, is_ref, T[N], e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, is_ref, const T[N], e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, is_ref, volatile T[N], e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, is_ref, const volatile T[N], e_false_v)
#		endif
#	else	/* !defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) */

	char EXTL_CDECL is_ref_helper1(...);
	// retrun type: T&(*)(type_wrap<T>) 
	template <typename_param_k T> 
	T&(* is_ref_helper1(type_wrap<T>))(type_wrap<T>);

	yes_type EXTL_CDECL is_ref_helper2(...);
	template <typename_param_k T> 
	no_type is_ref_helper2(T&(*)(type_wrap<T>)); // note: cannot exclude function type 

	//EXTL_BOOL_TRAIT_DEF_1(is_ref, sizeof(is_ref_helper2(is_ref_helper1(type_wrap<T>()))) == sizeof(yes_type))
	EXTL_BOOL_TRAIT_DEF_1(is_ref, (op_and	<	(sizeof(is_ref_helper2(is_ref_helper1(type_wrap<T>()))) == sizeof(yes_type))
											,	(op_not<(is_func<T>::value)>::value) /* exclude function type */
											>::value))

	EXTL_BOOL_TRAIT_SPEC_1(is_ref, void, e_false_v)
#		ifdef EXTL_CV_VOID_SPEC_SUPPORT
		EXTL_BOOL_TRAIT_SPEC_1(is_ref, void const, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_ref, void volatile, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_ref, void const volatile, e_false_v)
#		endif

#	endif	/* EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_ref_test.h"
#	endif
#endif	

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_REF_H */
/* //////////////////////////////////////////////////////////////////// */
