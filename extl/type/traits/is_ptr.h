/* ///////////////////////////////////////////////////////////////////////
 * File:		is_ptr.h		
 *
 * Created:		08.02.14				
 * Updated:		08.07.09
 *
 * Brief: is_ptr traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_PTR_H
#define EXTL_TYPE_TRAITS_IS_PTR_H

#ifndef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#	error extl::is_ptr is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_mem_ptr.h"
#include "is_ref.h"
#include "is_array.h"
#include "detail/is_func_ptr_tester.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_PTR(type)			EXTL_MUST_BE_(is_ptr, type)
#define EXTL_MUST_BE_CV_PTR(type)		EXTL_MUST_BE_CV_(is_ptr, type)

#define EXTL_MUST_NOT_BE_PTR(type)		EXTL_MUST_NOT_BE_(is_ptr, type)
#define EXTL_MUST_NOT_BE_CV_PTR(type)	EXTL_MUST_NOT_BE_CV_(is_ptr, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(is_ptr_helper, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ptr_helper, T*, e_true_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ptr_helper, T* const, e_true_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ptr_helper, T* volatile, e_true_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ptr_helper, T* const volatile, e_true_v)

EXTL_BOOL_TRAIT_DEF_1(is_ptr, (op_and< (is_ptr_helper<T>::value), (op_not< (is_mem_ptr<T>::value) >::value) >::value))

#		if defined(EXTL_COMPILER_IS_BORLAND) && (__BORLANDC__ < 0x600)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ptr, T&, e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ptr, T& const, e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ptr, T& volatile, e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_ptr, T& const volatile, e_false_v)
#		endif
#	else

		yes_type EXTL_CDECL is_ptr_tester(const volatile void*);
		no_type EXTL_CDECL is_ptr_tester(...);

		template < e_bool_t >
		struct is_ptr_helper
		{
			template < typename_param_k T>
			struct result
			{
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
			};
		};

		EXTL_TEMPLATE_SPECIALISATION
		struct is_ptr_helper< e_false_v >
		{
			template <typename_param_k T> 
			struct result
			{
				static T t;
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_or	<	(sizeof(yes_type) == sizeof(is_ptr_tester(t)))
																	,	(sizeof(yes_type) == sizeof(EXTL_NS_DETAIL(is_func_ptr_tester)(t)))
																	>::value));
			};
		};

		/* 排除数组与引用 */
		template <typename_param_k T>
		struct is_ptr_impl
			: is_ptr_helper	<	op_or	<	is_ref<T>::value 
										,	is_array<T>::value
										>::value
							>::template_qual_k result<T>
		{
		};
		EXTL_BOOL_TRAIT_DEF_1(is_ptr, is_ptr_impl<T>::value)

		EXTL_BOOL_TRAIT_SPEC_1(is_ptr, void, e_false_v)
#		ifdef EXTL_CV_VOID_SPEC_SUPPORT	
		EXTL_BOOL_TRAIT_SPEC_1(is_ptr, void const, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_ptr, void volatile, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_ptr, void const volatile, e_false_v)
#		endif
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_ptr_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_PTR_H */
/* //////////////////////////////////////////////////////////////////// */
