/* ///////////////////////////////////////////////////////////////////////
 * File:		is_volatile.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_volatile traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_VOLATILE_H
#define EXTL_TYPE_TRAITS_IS_VOLATILE_H

#ifndef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
#	error extl::is_volatile is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	include "is_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	include "is_array.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_BOUNDS_SUPPORT
#	include "remove_bounds.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_VOLATILE(type)			EXTL_MUST_BE_(is_volatile, type)
#define EXTL_MUST_NOT_BE_VOLATILE(type)		EXTL_MUST_NOT_BE_(is_volatile, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	if	defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) 

EXTL_BOOL_TRAIT_DEF_1(is_volatile_impl, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile_impl, T*, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile_impl, const T*, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile_impl, volatile T*, e_true_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile_impl, const volatile T*, e_true_v)

#		if EXTL_WORKAROUND_MSVC(<=, 1310)
		EXTL_BOOL_TRAIT_DEF_1(is_volatile, (is_volatile_impl< typename remove_bounds<T>::type* >::value))
#		else 
		EXTL_BOOL_TRAIT_DEF_1(is_volatile, (is_volatile_impl<T*>::value))
#endif

EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile, T&, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile, T*, e_false_v)

#		if EXTL_WORKAROUND_DMC(==, 0x850)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_volatile, T* const, e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_volatile, T* const volatile, e_true_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, is_volatile, T* volatile, e_true_v)
#		endif

#		if EXTL_WORKAROUND_BORLAND(<, 0x600)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile, T& const, e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile, T& volatile, e_false_v)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T, is_volatile, T& const volatile, e_false_v)
#		endif

#		if EXTL_WORKAROUND_GCC(<, 3)
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T,is_volatile,T const,!(is_ref<T>::value))
		EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(typename T,is_volatile,T volatile const,!(is_ref<T>::value))
#		endif

	EXTL_BOOL_TRAIT_SPEC_1(is_volatile, void, e_false_v)
#		ifdef EXTL_CV_VOID_SPEC_SUPPORT	
		EXTL_BOOL_TRAIT_SPEC_1(is_volatile, void const, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_volatile, void volatile, e_true_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_volatile, void const volatile, e_true_v)
#		endif

#	else 

	yes_type is_volatile_tester(const volatile void *);
	no_type is_volatile_tester(const void *);

	template < e_bool_t is_ref, e_bool_t is_array >
	struct is_volatile_helper
	{
		template <typename_param_k T> 
		struct result
		{
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
		};
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct is_volatile_helper<e_false_v, e_false_v>
	{
		template <typename_param_k T> 
		struct result
		{
			static T* t;
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(yes_type) == sizeof(is_volatile_tester(t))));
		};
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct is_volatile_helper<e_false_v, e_true_v>
	{
		template <typename_param_k T> 
		struct result
		{
			static T t;
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(yes_type) == sizeof(is_volatile_tester(&t))));
		};
	};

	template <typename_param_k T>
	struct is_volatile_impl
		: is_volatile_helper< (is_ref< T >::value), (is_array< T >::value) >::template result<T>
	{
	};

	EXTL_BOOL_TRAIT_DEF_1(is_volatile, is_volatile_impl<T>::value)

	EXTL_BOOL_TRAIT_SPEC_1(is_volatile, void, e_false_v)
#		ifdef EXTL_CV_VOID_SPEC_SUPPORT	
		EXTL_BOOL_TRAIT_SPEC_1(is_volatile, void const, e_false_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_volatile, void volatile, e_true_v)
		EXTL_BOOL_TRAIT_SPEC_1(is_volatile, void const volatile, e_true_v)
#		endif
	
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_volatile_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_VOLATILE_H */
/* //////////////////////////////////////////////////////////////////// */
