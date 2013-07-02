/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_ref.h		
 *
 * Created:		08.02.07				
 * Updated:		08.07.09
 *
 * Brief: remove_ref traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_REF_H
#define EXTL_TYPE_TRAITS_REMOVE_REF_H

#ifndef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
#	error extl::remove_ref is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_ref.h"

// only for VC 6.0,7.0,7.1
#if defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	include "detail/type_buffer.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_REMOVE_REF(src_type)	EXTL_MODIFY_TYPE(remove_ref, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

	EXTL_TYPE_TRAIT_DEF_1(remove_ref, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ref, T&, T)

#		if EXTL_WORKAROUND_BORLAND(<, 0x600)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ref, T& const, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ref, T& volatile, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ref, T& const volatile, T)
#		endif
#	elif EXTL_WORKAROUND_MSVC(<=, 1300)
		/* //////////////////////////////////////////////////////////////////// */
		template< e_bool_t is_ref >
		struct remove_ref_helper
		{
			template< typename_param_k T , typename_param_k ID >
			struct result
			{
				typedef T type; 
			};
		};
		EXTL_TEMPLATE_SPECIALISATION
		struct remove_ref_helper< e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(U&(*)());
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (T(*)())(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type; // save type
			};
		};

		template< typename_param_k T>
		struct remove_ref_impl
			: remove_ref_helper< (is_ref<T>::value) >::template_qual_k result<T, remove_ref_impl<T> >
		{

		};

		EXTL_TYPE_TRAIT_DEF_1(remove_ref, typename_type_k remove_ref_impl<T>::type )
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/remove_ref_test.h"
#	endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_REMOVE_REF_H */
/* //////////////////////////////////////////////////////////////////// */
