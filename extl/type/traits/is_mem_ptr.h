/* ///////////////////////////////////////////////////////////////////////
 * File:		is_mem_ptr.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_mem_ptr traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_MEM_PTR_H
#define EXTL_TYPE_TRAITS_IS_MEM_PTR_H

#ifndef EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#	error extl::is_mem_ptr is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "detail/is_mem_func_ptr_tester.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT
#	include "is_mem_func_ptr.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_MEM_PTR(type)			EXTL_MUST_BE_(is_mem_ptr, type)
#define EXTL_MUST_BE_CV_MEM_PTR(type)		EXTL_MUST_BE_CV_(is_mem_ptr, type)

#define EXTL_MUST_NOT_BE_MEM_PTR(type)		EXTL_MUST_NOT_BE_(is_mem_ptr, type)
#define EXTL_MUST_NOT_BE_CV_MEM_PTR(type)	EXTL_MUST_NOT_BE_CV_(is_mem_ptr, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
#		ifndef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT
		EXTL_BOOL_TRAIT_DEF_1(is_mem_ptr, e_false_v) 
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, typename_param_k U, is_mem_ptr, U T::*, e_true_v)
#		else 
		EXTL_BOOL_TRAIT_DEF_1(is_mem_ptr, is_mem_func_ptr<T>::value)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, typename_param_k U, is_mem_ptr, U T::*, e_true_v)
#		endif
#	else


	no_type EXTL_CDECL is_mem_ptr_tester(...);

	template <typename_param_k R, typename_param_k T>
	yes_type EXTL_CDECL is_mem_ptr_tester(R T::*);
	
	template <typename_param_k T>
	struct is_mem_ptr_impl
	{
		static T t;
#		ifdef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_or<
									(sizeof(EXTL_NS_DETAIL(is_mem_func_ptr_tester)(t)) == sizeof(yes_type)), 
									(sizeof(is_mem_ptr_tester(t)) == sizeof(yes_type))
									>::value));
#		else
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(is_mem_ptr_tester(t)) == sizeof(yes_type)));
#		endif
	};
	EXTL_BOOL_TRAIT_DEF_1(is_mem_ptr, is_mem_ptr_impl<T>::value)

#	endif /* EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT */

EXTL_BOOL_TRAIT_SPEC_1(is_mem_ptr, void, e_false_v)
#ifdef EXTL_CV_VOID_SPEC_SUPPORT	
	EXTL_BOOL_TRAIT_SPEC_1(is_mem_ptr, void const, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_mem_ptr, void volatile, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_mem_ptr, void const volatile, e_false_v)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_mem_ptr_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_MEM_PTR_H */
/* //////////////////////////////////////////////////////////////////// */
