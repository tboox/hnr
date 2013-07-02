/* ///////////////////////////////////////////////////////////////////////
 * File:		pow.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.09
 *
 * Brief: Caculate R = P^N
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_POW_H
#define EXTL_MPL_MATH_POW_H

/*!\file pow.h
 * \brief Caculate R = P^N
 *
 * Note: range from 0 to 62(64-bit) or 30(32-bit)
 */
#ifndef EXTL_MPL_MATH_POW_SUPPORT
#	error extl::pow is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "math.h"
#include "../int_.h"

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
#ifdef EXTL_MPL_IF_SUPPORT

/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_BEGIN_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
template < e_umax_int_t P, e_umax_int_t N, e_umax_int_t R >
struct pow_impl
{
	/* In order to decrease the number of instaniation and do not need partial specialization */
	typedef typename_type_k if_<	(N > 0) 
								,	pow_impl< P, N - 1, P * R > 
								,	umax_int_<R>
								>::type result_t;

	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = result_t::value);

	/* The number of instaniation is very much and needs partial specialization */
	/* EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = ((N > 0)? (pow_impl< P, N-1, P * R >::value)) : R); */
};

/* VECTORC: need partial specialization */
#	if defined(EXTL_COMPILER_IS_VECTORC) && \
		defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT)
template < e_umax_int_t P, e_umax_int_t R >
struct pow_impl<P, 0, R>
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = R);
};
#	endif
/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_END_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
/*!\brief: pow class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t P, e_umax_int_t N >
struct pow
	: EXTL_NS_DETAIL(pow_impl)< P, N, 1 >
{
};
/*!\brief: pow_2 class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t N >
struct pow_2
	: EXTL_NS_DETAIL(pow_impl)< 2, N, 1 >
{
};
/*!\brief: pow_10 class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t N >
struct pow_10
	: EXTL_NS_DETAIL(pow_impl)< 10, N, 1 >
{
};
/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#ifdef EXTL_MPL_MATH_POW_TEST_ENABLE
#	include "unit_test/pow_test.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_IF_SUPPORT */
#endif /* EXTL_MPL_SUPPORT */
/* //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_POW_H */
/* //////////////////////////////////////////////////////////////////// */
