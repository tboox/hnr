/* ///////////////////////////////////////////////////////////////////////
 * File:		if_.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief: if_ class - type select
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_IF_H
#define EXTL_MPL_IF_H

/*!\file if_.h
 * \brief if_ class - logical operation 
 */
#ifndef EXTL_MPL_IF_SUPPORT
#	error extl::mpl::if_ is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef	EXTL_MPL_IF_TEST_ENABLE
#	include "../type/traits/is_void.h"
#	include "../type/traits/is_int.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_BEGIN_WHOLE_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifdef EXTL_MPL_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
#	if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) && \
		!defined(EXTL_COMPILER_IS_BORLAND)
/*!\brief: if_ class
 * 
 * \ingroup extl_group_mpl
 */
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
/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_BEGIN_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
template < e_bool_t C >
struct if_impl
{
	template < typename_param_k T0, typename_param_k T1 > 
	struct result;
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
/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_END_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
/*!\brief: if_ class
 * 
 * \ingroup extl_group_mpl
 */
template < e_bool_t C1, typename_param_k T1, typename_param_k T2 >
struct if_
	: EXTL_NS_DETAIL(if_impl)< C1 >::template_qual_k result< T1, T2 >
{
};
#	endif
/*!\brief: if_2_ class
 * 
 * \ingroup extl_group_mpl
 */
template < e_bool_t C1, e_bool_t C2, typename_param_k T1, typename_param_k T2, typename_param_k T3 >
struct if_2_
{
	typedef typename_type_k if_<	C1
								,	T1
								,	typename_type_k if_<	C2
														,	T2
														,	T3
														>::type
								>::type type;
};

/*!\brief: if_3_ class
 * 
 * \ingroup extl_group_mpl
 */
template < e_bool_t C1, e_bool_t C2, e_bool_t C3, typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4 >
struct if_3_
{
	typedef typename_type_k if_2_<	C1
								,	C2
								,	T1
								,	T2
								,	typename_type_k if_<	C3
														,	T3
														,	T4
														>::type
								>::type type;
};



/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#	ifdef EXTL_MPL_IF_TEST_ENABLE
#		include "unit_test/if_test.h"
#	endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_SUPPORT */
/* //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MPL_IF_H */
/* //////////////////////////////////////////////////////////////////// */
