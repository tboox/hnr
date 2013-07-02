/* ///////////////////////////////////////////////////////////////////////
 * File:		sqrt.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.09
 *
 * Brief: Caculate P = sqrt<N> ==> N = P^2
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_SQRT_H
#define EXTL_MPL_MATH_SQRT_H

/*!\file sqrt.h
 * \brief Caculate P = sqrt<N> ==> N = P^2
 */
#ifndef EXTL_MPL_MATH_SQRT_SUPPORT
#	error extl::sqrt is not supported by current compiler.
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

/* ///////////////////////////////////////////////////////////////////////
 * Binary Search Method
 * Rounded down
 * Fast, but prone to overflow
 * //////////////////////////////////////////////////////////////////// */
#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) && \
		!defined(EXTL_COMPILER_IS_DMC) && \
			!defined(EXTL_COMPILER_IS_BORLAND) 
/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_BEGIN_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
template < e_umax_int_t N, e_umax_int_t L = 0, e_umax_int_t H = N >
struct sqrt_impl
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, mid = (L + H + 1) / 2);

	/* In order to decrease the number of instaniation */
#	ifdef EXTL_MPL_IF_SUPPORT
	typedef typename_type_k if_<	(N < (mid * mid)) 
								,	sqrt_impl<N, L, (mid - 1)>
								,	sqrt_impl<N, mid, H> 
								>::type		result_t;

	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = result_t::value);
#	else
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = ((N < (mid * mid))? 
													(sqrt_impl<N, L, mid - 1>::value) : (sqrt_impl<N, mid, H>::value)));
#	endif

};

template < e_umax_int_t N, e_umax_int_t R >
struct sqrt_impl<N, R, R>
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = R);
};
/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_END_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
/*!\brief: sqrt class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t N >
struct sqrt
		: EXTL_NS_DETAIL(sqrt_impl)<N, 0, N>
{
};
#else

/* ///////////////////////////////////////////////////////////////////////
 * Iteration Method
 * Rounded down
 * Slow, but not easy to overflow
 * //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_BEGIN_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
template < e_umax_int_t N, e_umax_int_t I = 0 >
struct sqrt_impl
{
	/* In order to decrease the number of instaniation */
#	ifdef EXTL_MPL_IF_SUPPORT

	/* Rounded up */
	/*typedef typename_type_k if_<	((I * I) < N) 
								,	sqrt_impl<N, I+1>
								,	umax_int_<I> 
								>::type result_t;*/
	/* Rounded down */
#		ifdef EXTL_COMPILER_IS_BORLAND
	typedef typename_type_k if_<	((I * I) < N) 
								,	sqrt_impl<N, I+1> 
								,	typename_type_k if_<	((I * I) > N) 
														,	umax_int_<I-1> 
														,	umax_int_<I>
														>::type
								>::type result_t;
#		else
	typedef typename_type_k if_<	((I * I) < N) 
								,	sqrt_impl<N, I+1> 
								,	typename_type_k if_<	((I * I) > N) 
														,	typename_type_k umax_int_<I>::prior 
														,	umax_int_<I>
														>::type
								>::type result_t;
#		endif

	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = result_t::value);
#	endif

	/* Needs instaniation of all even if the result have been caculated */
	/*template < e_umax_int_t N >
	struct sqrt_impl<N, M>
	{
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = N);
	};*/
	/* EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = ((I * I) < N)? 
													(sqrt_impl<N, I+1>::value) : I)); */

};
/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_END_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
/*!\brief: sqrt class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t N >
struct sqrt : EXTL_NS_DETAIL(sqrt_impl)<N, 0>
{
};
#endif /* EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#ifdef EXTL_MPL_MATH_SQRT_TEST_ENABLE
#	include "unit_test/sqrt_test.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_SUPPORT */
/* //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_SQRT_H */
/* //////////////////////////////////////////////////////////////////// */
