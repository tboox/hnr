/* ///////////////////////////////////////////////////////////////////////
 * File:		is_class.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09
 *
 * Brief: is_class traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CLASS_H
#define EXTL_TYPE_TRAITS_IS_CLASS_H

#ifndef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#	error extl::is_class is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT
#	include "is_union.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	include "remove_cv.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_CLASS(type)		EXTL_MUST_BE_(is_class, type)
#define EXTL_MUST_BE_CV_CLASS(type)		EXTL_MUST_BE_CV_(is_class, type)

#define EXTL_MUST_NOT_BE_CLASS(type)	EXTL_MUST_NOT_BE_(is_class, type)
#define EXTL_MUST_NOT_BE_CV_CLASS(type)	EXTL_MUST_NOT_BE_CV_(is_class, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT

	template < typename_param_k T >
	no_type EXTL_CDECL is_class_tester(...);
	template < typename_param_k T >
	yes_type is_class_tester(void(T::*)(void));

	template < typename_param_k T >
	struct is_class_impl
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_and	<	(sizeof(yes_type)==sizeof(is_class_tester<T>( 0 )))
															,	(op_not< (is_union<T>::value ) >::value)

															>::value));
	};

#		ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
			EXTL_BOOL_TRAIT_DEF_1(is_class, is_class_impl< typename_type_k remove_cv<T>::type >::value)
#		else
			EXTL_BOOL_TRAIT_DEF_1(is_class, is_class_impl< T >::value)
#		endif

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_class_test.h"
#	endif
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_CLASS_H */
/* //////////////////////////////////////////////////////////////////// */
