/* ///////////////////////////////////////////////////////////////////////
 * File:		is_prime.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief: is_prime<N>
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_IS_PRIME_H
#define EXTL_MPL_MATH_IS_PRIME_H

/*!\file is_prime.h
 * \brief is_prime<N>
 * 
 * Note: range from 0 to 1000
 */

/* #ifndef EXTL_MPL_MATH_IS_PRIME_SUPPORT
#	error extl::is_prime is not supported by current compiler.
#endif */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "math.h"
#include "../int_.h"
#include "../bool_.h"

#ifdef EXTL_MPL_IF_SUPPORT
#	include "../if_.h"
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

/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_BEGIN_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
template < e_umax_int_t N , e_umax_int_t I >
struct is_prime_impl
{
	/* In order to decrease the number of instaniation */
#	ifdef EXTL_MPL_IF_SUPPORT
	typedef typename_type_k if_2_<	(N == 2) 
								,	((N % I) != 0)
								,	bool_< e_true_v > 
#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
								,	is_prime_impl< N, (I - 1) >
#	else
								,	is_prime_impl< ((I > 2)? N : 0), (I - 1) >
#	endif
								,	bool_< e_false_v >
								>::type result_t;

	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = result_t::value);
#	else
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (N == 2) || ((N%I) && (is_prime_impl< ((I > 2)? N : 0), (I - 1) >::value)));
#	endif
};

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT)
template < e_umax_int_t N >
struct is_prime_impl<N, 0>
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};
template < e_umax_int_t N >
struct is_prime_impl<N, 1>
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};
#else
EXTL_TEMPLATE_SPECIALISATION
struct is_prime_impl<0, 0>
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};

EXTL_TEMPLATE_SPECIALISATION
struct is_prime_impl<0, 1>
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};
#endif


/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_END_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
/*!\brief: is_prime class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t N >
struct is_prime
	: EXTL_NS_DETAIL(is_prime_impl)<N, N-1>
{
};
EXTL_TEMPLATE_SPECIALISATION
struct is_prime<0>
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};
EXTL_TEMPLATE_SPECIALISATION
struct is_prime<1>
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#ifdef EXTL_MPL_MATH_IS_PRIME_TEST_ENABLE
#	include "unit_test/is_prime_test.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_SUPPORT */
/* //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_IS_PRIME_H */
/* //////////////////////////////////////////////////////////////////// */
