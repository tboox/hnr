/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_const.h		
 *
 * Created:		08.02.07				
 * Updated:		08.07.09
 *
 * Brief: remove_const traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_CONST_H
#define EXTL_TYPE_TRAITS_REMOVE_CONST_H

#ifndef EXTL_TYPE_TRAITS_REMOVE_CONST_SUPPORT
#	error extl::remove_const is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#	include "is_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
#	include "is_const.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
#	include "is_volatile.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	include "is_array.h"
#endif

// only for VC 6.0,7.0,7.1
#if defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	include "detail/type_buffer.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_REMOVE_CONST(src_type)	EXTL_MODIFY_TYPE(remove_const, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

	EXTL_TYPE_TRAIT_DEF_1(remove_const_impl, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_const_impl, T*, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_const_impl, const T*, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_const_impl, volatile T*, volatile T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_const_impl, const volatile T*, volatile T)

	EXTL_TYPE_TRAIT_DEF_1(remove_const, typename_type_k remove_const_impl<T*>::type)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_const, T&, T&)

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_ARRAY_TYPE_SUPPORT
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_TO_ARRAY_1_2(typename_param_k T, e_size_t N, remove_const, T const[N], T type[N])
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_TO_ARRAY_1_2(typename_param_k T, e_size_t N, remove_const, T const volatile [N], T volatile type[N])
#	endif

#	elif EXTL_WORKAROUND_MSVC(<=, 1300)
		/* //////////////////////////////////////////////////////////////////// */
		template< e_bool_t is_ptr, e_bool_t is_array, e_bool_t is_const, e_bool_t is_volatile >
		struct remove_const_helper
		{
			template< typename_param_k T , typename_param_k ID >
			struct result
			{
				typedef T type; 
			};
			template< typename_param_k T >
            struct transform_type 
			{
                typedef T type;
            };
		};
		EXTL_TEMPLATE_SPECIALISATION	// const 
		struct remove_const_helper< e_false_v, e_false_v, e_true_v , e_false_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(U const&(*)());
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (T(*)())(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type;
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T& type;	// exclude const&
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// cv 
		struct remove_const_helper< e_false_v, e_false_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U volatile, ID> test(U const volatile&(*)());
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (T(*)())(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type;
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T& type;	// exclude const&
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// const ptr 
		struct remove_const_helper< e_true_v, e_false_v, e_true_v , e_false_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(void(*)(U const[]));
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (void(*)(T))(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type;
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T type[];
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// cv ptr 
		struct remove_const_helper< e_true_v, e_false_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U volatile, ID> test(void(*)(U const volatile[])); 
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (void(*)(T))(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type; 
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T type[];
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// const array 
		struct remove_const_helper< e_false_v, e_true_v, e_true_v , e_false_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				EXTL_STATIC_MEMBER_CONST(e_size_t, num = (sizeof(T)/sizeof((*((T*)NULL))[0])) ); 

				template< typename_param_k U >
				static save_type<U[num], ID> test(void(*)(U const[])); 
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (void(*)(T))(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type; 
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T type;
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// cv array 
		struct remove_const_helper< e_false_v, e_true_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				EXTL_STATIC_MEMBER_CONST(e_size_t, num = (sizeof(T)/sizeof((*((T*)NULL))[0])) ); 

				template< typename_param_k U >
				static save_type<U volatile[num], ID> test(void(*)(U const volatile[]));
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (void(*)(T))(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type; 
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T type;
            };
		};

		template< typename_param_k T>
		struct remove_const_impl
		{
			typedef remove_const_helper	<	(is_ptr<T>::value) 
										,	(is_array<T>::value)
										,	(is_const<T>::value) 
										,	(is_volatile<T>::value) 
										>	remove_const_type;

			typedef typename_type_k remove_const_type::template_qual_k result< 
										typename_type_k remove_const_type::template_qual_k transform_type<T>::type
									,	remove_const_impl<T> 
									>::type	type;

		};

		EXTL_TYPE_TRAIT_DEF_1(remove_const, typename_type_k remove_const_impl<T>::type)

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/remove_const_test.h"
#	endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_REMOVE_CONST_H */
/* //////////////////////////////////////////////////////////////////// */
