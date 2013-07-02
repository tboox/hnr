/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_volatile.h		
 *
 * Created:		08.02.07				
 * Updated:		08.07.09
 *
 * Brief: remove_volatile traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_VOLATILE_H
#define EXTL_TYPE_TRAITS_REMOVE_VOLATILE_H

#ifndef EXTL_TYPE_TRAITS_REMOVE_VOLATILE_SUPPORT
#	error extl::remove_volatile is not supported by current compiler.
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
#define EXTL_REMOVE_VOLATILE(src_type)	EXTL_MODIFY_TYPE(remove_volatile, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

	EXTL_TYPE_TRAIT_DEF_1(remove_volatile_impl, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_volatile_impl, T*, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_volatile_impl, volatile T*, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_volatile_impl, const T*, const T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_volatile_impl, const volatile T*, const T)

	EXTL_TYPE_TRAIT_DEF_1(remove_volatile, typename_type_k remove_volatile_impl<T*>::type)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_volatile, T&, T&)

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_ARRAY_TYPE_SUPPORT
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_TO_ARRAY_1_2(typename_param_k T, e_size_t N, remove_volatile, T volatile[N], T type[N])
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_TO_ARRAY_1_2(typename_param_k T, e_size_t N, remove_volatile, T const volatile [N], T const type[N])
#	endif

#	elif EXTL_WORKAROUND_MSVC(<=, 1300)
		/* //////////////////////////////////////////////////////////////////// */
		template< e_bool_t is_ptr, e_bool_t is_array, e_bool_t is_const, e_bool_t is_volatile >
		struct remove_volatile_helper
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
		EXTL_TEMPLATE_SPECIALISATION	// volatile 
		struct remove_volatile_helper< e_false_v, e_false_v, e_false_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(U volatile&(*)());
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (T(*)())(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type;
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T& type;	
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// cv 
		struct remove_volatile_helper< e_false_v, e_false_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U const, ID> test(U const volatile&(*)());
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (T(*)())(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type;
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T& type;	
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// volatile ptr 
		struct remove_volatile_helper< e_true_v, e_false_v, e_false_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(void(*)(U volatile[]));
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
		struct remove_volatile_helper< e_true_v, e_false_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U const, ID> test(void(*)(U const volatile[])); 
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

		EXTL_TEMPLATE_SPECIALISATION	// volatile array 
		struct remove_volatile_helper< e_false_v, e_true_v, e_false_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				EXTL_STATIC_MEMBER_CONST(e_size_t, num = (sizeof(T)/sizeof((*((T*)NULL))[0])) ); 

				template< typename_param_k U >
				static save_type<U[num], ID> test(void(*)(U volatile[])); 
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
		struct remove_volatile_helper< e_false_v, e_true_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				EXTL_STATIC_MEMBER_CONST(e_size_t, num = (sizeof(T)/sizeof((*((T*)NULL))[0])) ); 

				template< typename_param_k U >
				static save_type<U const[num], ID> test(void(*)(U const volatile[])); /* 原类型: U const volatile [] 或 T */
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (void(*)(T))(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type; /* 新类型: U volatile [num] 或 T */
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T type;
            };
		};

		template< typename_param_k T>
		struct remove_volatile_impl
		{
			typedef remove_volatile_helper	<	(is_ptr<T>::value) 
											,	(is_array<T>::value)
											,	(is_const<T>::value) 
											,	(is_volatile<T>::value) 
											>	remove_volatile_type;

			typedef typename_type_k remove_volatile_type::template_qual_k result< 
										typename_type_k remove_volatile_type::template_qual_k transform_type<T>::type
									,	remove_volatile_impl<T> 
									>::type	type;

		};

		EXTL_TYPE_TRAIT_DEF_1(remove_volatile, typename_type_k remove_volatile_impl<T>::type )

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/remove_volatile_test.h"
#	endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_REMOVE_VOLATILE_H */
/* //////////////////////////////////////////////////////////////////// */
