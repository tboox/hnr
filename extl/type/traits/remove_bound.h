/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_bound.h		
 *
 * Created:		08.02.07				
 * Updated:		08.07.09
 *
 * Brief: remove_bound traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_BOUND_H
#define EXTL_TYPE_TRAITS_REMOVE_BOUND_H

#ifndef EXTL_TYPE_TRAITS_REMOVE_BOUND_SUPPORT
#	error extl::remove_bound is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	include "is_array.h"
#endif

#if !defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_H) && \
		(defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER <= 1300))
#	include "detail/type_buffer.h"
#endif

#ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#	include "is_arithmetic.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_REMOVE_BOUND(src_type)	EXTL_MODIFY_TYPE(remove_bound, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_ARRAY_TYPE_SUPPORT

	EXTL_TYPE_TRAIT_DEF_1(remove_bound, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, remove_bound, T[N], T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, remove_bound, T const[N], T const)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, remove_bound, T volatile[N], T volatile)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_2(typename_param_k T, e_size_t N, remove_bound, T const volatile[N], T const volatile)

#		if !EXTL_WORKAROUND_BORLAND(<, 0x600) && \
				!(defined(EXTL_COMPILER_IS_DMC)) && \
					!defined(EXTL_COMPILER_IS_VECTORC)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_bound, T[], T)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_bound, T const[], T const)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_bound, T volatile[], T volatile)
		EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_bound, T const volatile[], T const volatile)
#		endif

#	elif EXTL_WORKAROUND_MSVC(<=, 1300)
		/* //////////////////////////////////////////////////////////////////// */
		template< e_bool_t is_array >
		struct remove_bound_helper
		{
			template< typename_param_k T , typename_param_k ID >
			struct result
			{
				typedef T type;
			};
		};
		EXTL_TEMPLATE_SPECIALISATION
		struct remove_bound_helper< e_true_v > 
		{
			template< typename_param_k T , typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(U[]);
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( *((T*)NULL) ) ));
				typedef typename_type_k type_buffer<ID>::result::type type; 
			};
		};


		template<typename_param_k T>
		struct remove_bound_impl
			: remove_bound_helper< (is_array<T>::value) >::template_qual_k result<T, remove_bound_impl<T> >
		{

		};

		EXTL_TYPE_TRAIT_DEF_1(remove_bound, typename_type_k remove_bound_impl<T>::type )

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/remove_bound_test.h"
#	endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_REMOVE_BOUND_H */
/* //////////////////////////////////////////////////////////////////// */
