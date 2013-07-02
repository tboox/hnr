/* ///////////////////////////////////////////////////////////////////////
 * File:		is_class_or_union.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09
 *
 * Brief: is_class_or_union traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_H
#define EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_H

#ifndef EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_SUPPORT
#	error extl::is_class_or_union is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_arithmetic.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	include "remove_cv.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_CLASS_OR_UNION(type)			EXTL_MUST_BE_(is_class_or_union, type)
#define EXTL_MUST_BE_CV_CLASS_OR_UNION(type)		EXTL_MUST_BE_CV_(is_class_or_union, type)

#define EXTL_MUST_NOT_BE_CLASS_OR_UNION(type)		EXTL_MUST_NOT_BE_(is_class_or_union, type)
#define EXTL_MUST_NOT_BE_CV_CLASS_OR_UNION(type)	EXTL_MUST_NOT_BE_CV_(is_class_or_union, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

/* is_class_or_union 特性定义 */
template < typename_param_k T >
no_type EXTL_CDECL is_class_or_union_tester(...);

template < typename_param_k T >
//yes_type is_class_or_union_tester(void(T::*)(void));
yes_type is_class_or_union_tester(e_int_t T::*);

template < typename_param_k T >
struct is_class_or_union_impl
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(yes_type) == sizeof(is_class_or_union_tester<T>( 0 ))));
};

#	ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
		EXTL_BOOL_TRAIT_DEF_1(is_class_or_union, is_class_or_union_impl< typename_type_k remove_cv<T>::type >::value)
#	else
		EXTL_BOOL_TRAIT_DEF_1(is_class_or_union, is_class_or_union_impl< T >::value)
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_class_or_union_test.h"
#	endif

#endif 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_H */
/* //////////////////////////////////////////////////////////////////// */
