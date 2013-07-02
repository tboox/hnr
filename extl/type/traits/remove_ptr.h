/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_ptr.h		
 *
 * Created:		08.02.07				
 * Updated:		08.07.09
 *
 * Brief: remove_ptr traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_PTR_H
#define EXTL_TYPE_TRAITS_REMOVE_PTR_H

#ifndef EXTL_TYPE_TRAITS_REMOVE_PTR_SUPPORT
#	error extl::remove_ptr is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#	include "is_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	include "remove_cv.h"
#endif

// only for VC 6.0,7.0,7.1
#if defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	include "detail/type_buffer.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_REMOVE_PTR(src_type)	EXTL_MODIFY_TYPE(remove_ptr, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

#		if defined(EXTL_COMPILER_IS_VECTORC) && \
			defined(EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT) 

		EXTL_TYPE_TRAIT_DEF_1(remove_ptr_impl, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ptr_impl, T*, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ptr_impl, T* const, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ptr_impl, T* volatile, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ptr_impl, T* const volatile, T)

		EXTL_TYPE_TRAIT_DEF_1(remove_ptr, typename_type_k remove_ptr_impl< typename_type_k remove_cv<T>::type >::type )

#		else

		EXTL_TYPE_TRAIT_DEF_1(remove_ptr, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ptr, T*, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ptr, T* const, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ptr, T* volatile, T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_ptr, T* const volatile, T)

#		endif

#	elif EXTL_WORKAROUND_MSVC(<=, 1300)
		/* //////////////////////////////////////////////////////////////////// */
		template< e_bool_t is_ptr >
		struct remove_ptr_helper
		{
			template< typename_param_k T , typename_param_k ID >
			struct result
			{
				typedef T type; 
			};
		};
		EXTL_TEMPLATE_SPECIALISATION
		struct remove_ptr_helper< e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(U*);
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( *((T*)NULL) ) )); // select type 
				typedef typename_type_k type_buffer<ID>::result::type type; // save type 
			};
		};

		template< typename_param_k T>
		struct remove_ptr_impl	// ID: only for identification
			: remove_ptr_helper< (is_ptr<T>::value) >::template_qual_k result<T, remove_ptr_impl<T> > 
		{

		};

		EXTL_TYPE_TRAIT_DEF_1(remove_ptr, typename_type_k remove_ptr_impl<T>::type )

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/remove_ptr_test.h"
#	endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_REMOVE_PTR_H */
/* //////////////////////////////////////////////////////////////////// */
