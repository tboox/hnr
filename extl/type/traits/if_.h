/* ///////////////////////////////////////////////////////////////////////
 * File:		if_.h		
 *
 * Created:		08.03.16					
 * Updated:		08.07.09
 *
 * Brief: if_ class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IF_H
#define EXTL_TYPE_TRAITS_IF_H

#ifndef EXTL_TYPE_TRAITS_IF_SUPPORT
#	error extl::if_ is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#	include "is_void.h"
#	include "is_int.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
#	if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) && \
		!defined(EXTL_COMPILER_IS_BORLAND)
template < e_bool_t C, typename_param_k T0, typename_param_k T1 >
struct if_
{
	typedef T1 type;
};

template < typename_param_k T0, typename_param_k T1 >
struct if_< e_true_v, T0, T1 >
{
	typedef T0 type;
};

template < typename_param_k T0, typename_param_k T1 >
struct if_< e_false_v, T0, T1 >
{
	typedef T1 type;
};
#	else
/* ///////////////////////////////////////////////////////////////////////
 * ::detail namespace
 */
EXTL_DETAIL_BEGIN_NAMESPACE 

template < e_bool_t C >
struct if_impl
{
	template < typename_param_k T0, typename_param_k T1 > 
	struct result{};
};

EXTL_TEMPLATE_SPECIALISATION
struct if_impl< e_true_v >
{
	template < typename_param_k T0, typename_param_k T1 > 
	struct result
	{
		typedef T0 type;
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct if_impl< e_false_v >
{
	template < typename_param_k T0, typename_param_k T1 > 
	struct result
	{
		typedef T1 type;
	};
};
/* ///////////////////////////////////////////////////////////////////////
 * ::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE 

template < e_bool_t C1, typename_param_k T1, typename_param_k T2 >
struct if_
	: EXTL_NS_DETAIL(if_impl)< C1 >::template_qual_k result< T1, T2 >
{
};
#	endif
template < e_bool_t C1, e_bool_t C2, typename_param_k T1, typename_param_k T2, typename_param_k T3 >
struct if_2_
{
	typedef typename_type_k if_	<	C1
								,	T1
								,	typename_type_k if_<	C2
														,	T2
														,	T3
														>::type
								>::type type;
};

template < e_bool_t C1, e_bool_t C2, e_bool_t C3, typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4 >
struct if_3_
{
	typedef typename_type_k if_2_	<	C1
									,	C2
									,	T1
									,	T2
									,	typename_type_k if_	<	C3
															,	T3
															,	T4
															>::type
									>::type type;
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/if_test.h"
#	endif

#endif 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IF_H */
/* //////////////////////////////////////////////////////////////////// */
