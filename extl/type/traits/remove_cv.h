/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_cv.h		
 *
 * Created:		08.02.07				
 * Updated:		08.07.09
 *
 * Brief: remove_cv traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_CV_H
#define EXTL_TYPE_TRAITS_REMOVE_CV_H

#ifndef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	error extl::remove_cv is not supported by current compiler.
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

#ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#	ifdef EXTL_TYPE_TRAITS_IS_CV_SUPPORT
#		include "is_cv.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_REMOVE_CV(src_type)	EXTL_MODIFY_TYPE(remove_cv, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

	EXTL_TYPE_TRAIT_DEF_1(remove_cv_impl, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_cv_impl, T*, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_cv_impl, const T*, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_cv_impl, volatile T*, T)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_cv_impl, const  volatile T*, T)

	EXTL_TYPE_TRAIT_DEF_1(remove_cv, typename_type_k remove_cv_impl<T*>::type)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, remove_cv, T&, T&)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_TO_ARRAY_1_2(typename_param_k T, e_size_t N, remove_cv, T const[N], T type[N])
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_TO_ARRAY_1_2(typename_param_k T, e_size_t N, remove_cv, T volatile [N], T type[N])
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_TO_ARRAY_1_2(typename_param_k T, e_size_t N, remove_cv, T const volatile [N], T type[N])

#	elif EXTL_WORKAROUND_MSVC(<=, 1300)
		/* //////////////////////////////////////////////////////////////////// */
		template< e_bool_t is_ptr, e_bool_t is_array, e_bool_t is_const, e_bool_t is_cv >
		struct remove_cv_helper
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
		struct remove_cv_helper< e_false_v, e_false_v, e_true_v, e_false_v  > 
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

		EXTL_TEMPLATE_SPECIALISATION	// volatile 
		struct remove_cv_helper< e_false_v, e_false_v, e_false_v , e_true_v > 
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
                typedef T& type;	// exclude volatile&
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// cv 
		struct remove_cv_helper< e_false_v, e_false_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(U const volatile&(*)());
				static save_type<T, ID> test(...);
				EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test( (T(*)())(NULL) ) )); 
				typedef typename_type_k type_buffer<ID>::result::type type;
			};
			template< typename_param_k T >
            struct transform_type
			{
                typedef T& type;	// exclude const volatile&
            };
		};

		EXTL_TEMPLATE_SPECIALISATION	// const ptr 
		struct remove_cv_helper< e_true_v, e_false_v, e_true_v, e_false_v  > 
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

		EXTL_TEMPLATE_SPECIALISATION	// volatile ptr 
		struct remove_cv_helper< e_true_v, e_false_v, e_false_v , e_true_v > 
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
		struct remove_cv_helper< e_true_v, e_false_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				template< typename_param_k U >
				static save_type<U, ID> test(void(*)(U const volatile[])); 
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
		struct remove_cv_helper< e_false_v, e_true_v, e_true_v , e_false_v > 
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

		EXTL_TEMPLATE_SPECIALISATION	// volatile array 
		struct remove_cv_helper< e_false_v, e_true_v, e_false_v , e_true_v > 
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
		struct remove_cv_helper< e_false_v, e_true_v, e_true_v , e_true_v > 
		{
			template< typename_param_k T, typename_param_k ID >
			struct result
			{
				EXTL_STATIC_MEMBER_CONST(e_size_t, num = (sizeof(T)/sizeof((*((T*)NULL))[0])) ); 

				template< typename_param_k U >
				static save_type<U[num], ID> test(void(*)(U const volatile[])); 
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
		struct remove_cv_impl
		{
			typedef remove_cv_helper<	(is_ptr<T>::value) 
									,	(is_array<T>::value)
									,	(is_const<T>::value) 
									,	(is_volatile<T>::value) 
									>	remove_cv_type;

			typedef typename_type_k remove_cv_type::template_qual_k result< 
										typename_type_k remove_cv_type::template_qual_k transform_type<T>::type
									,	remove_cv_impl<T>
									>::type	type;

		};

		EXTL_TYPE_TRAIT_DEF_1(remove_cv, typename_type_k remove_cv_impl<T>::type )

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/remove_cv_test.h"
#	endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_REMOVE_CV_H */
/* //////////////////////////////////////////////////////////////////// */
