/* ///////////////////////////////////////////////////////////////////////
 * File:		is_abstract.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09
 *
 * Brief: is_abstract traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_ABSTRACT_H
#define EXTL_TYPE_TRAITS_IS_ABSTRACT_H

#ifndef EXTL_TYPE_TRAITS_IS_ABSTRACT_SUPPORT
#	error extl::is_abstract is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#	include "is_class.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_ABSTRACT(type)			EXTL_MUST_BE_(is_abstract, type)
#define EXTL_MUST_BE_CV_ABSTRACT(type)		EXTL_MUST_BE_CV_(is_abstract, type)

#define EXTL_MUST_NOT_BE_ABSTRACT(type)		EXTL_MUST_NOT_BE_(is_abstract, type)
#define EXTL_MUST_NOT_BE_CV_ABSTRACT(type)	EXTL_MUST_NOT_BE_CV_(is_abstract, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
template < typename_param_k T >
no_type is_abstract_tester(T (*)[1]);
template < typename_param_k T >
yes_type EXTL_CDECL is_abstract_tester(...);

template < e_bool_t is_class >
struct is_abstract_helper
{
	template < typename_param_k T >
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct is_abstract_helper< e_true_v >
{
	template < typename_param_k T >
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(yes_type) == sizeof(is_abstract_tester<T>( 0 ))));
	};
};

template < typename_param_k T >
struct is_abstract_impl
	: is_abstract_helper< (is_class<T>::value) >::template_qual_k result<T>
{
};

EXTL_BOOL_TRAIT_DEF_1(is_abstract, is_abstract_impl< T >::value)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_abstract_test.h"
#	endif
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_ABSTRACT_H */
/* //////////////////////////////////////////////////////////////////// */
