/* ///////////////////////////////////////////////////////////////////////
 * File:		is_pod.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_pod traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_POD_H
#define EXTL_TYPE_TRAITS_IS_POD_H

#ifndef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	error extl::is_pod is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_void.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#	include "is_scalar.h"
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
#define EXTL_MUST_BE_POD(type)			EXTL_MUST_BE_(is_pod, type)
#define EXTL_MUST_BE_CV_POD(type)		EXTL_MUST_BE_CV_(is_pod, type)

#define EXTL_MUST_NOT_BE_POD(type)		EXTL_MUST_NOT_BE_(is_pod, type)
#define EXTL_MUST_NOT_BE_CV_POD(type)	EXTL_MUST_NOT_BE_CV_(is_pod, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

template < e_bool_t is_array >
struct is_pod_helper
{
	template < typename_param_k T >
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
	};

};

EXTL_TEMPLATE_SPECIALISATION
struct is_pod_helper< e_false_v >
{
	template < typename_param_k T >
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_or	<	(is_scalar<T>::value) 
															,	(is_void<T>::value) 
															,	EXTL_IS_POD_(T) 
															>::value));
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct is_pod_helper< e_true_v >
{
	template < typename_param_k T >
	struct result
	{
		typedef typename_type_k remove_bounds<T>::type reduced_type;

		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_or	<	(is_scalar<reduced_type>::value) 
															,	(is_void<reduced_type>::value) 
															,	EXTL_IS_POD_(reduced_type) 
															>::value));
	};
};

template < typename_param_k T >
struct is_pod_impl
	: is_pod_helper< (is_array<T>::value) >::template_qual_k result<T>
{

};

EXTL_BOOL_TRAIT_DEF_1(is_pod, is_pod_impl<T>::value )

EXTL_BOOL_TRAIT_SPEC_1(is_pod, void, e_true_v)
#ifdef EXTL_CV_VOID_SPEC_SUPPORT	
	EXTL_BOOL_TRAIT_SPEC_1(is_pod, void const, e_true_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_pod, void volatile, e_true_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_pod, void const volatile, e_true_v)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#	include "unit_test/is_pod_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_POD_H */
/* //////////////////////////////////////////////////////////////////// */
