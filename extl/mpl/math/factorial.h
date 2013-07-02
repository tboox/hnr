/* ///////////////////////////////////////////////////////////////////////
 * File:		factorial.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.09
 *
 * Brief: Caculate N!
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_FACTORIAL_H
#define EXTL_MPL_MATH_FACTORIAL_H

/*!\file factorial.h
 * \brief Caculate N!
 */

/*#ifndef EXTL_MPL_MATH_FACTORIAL_SUPPORT
#	error extl::factorial is not supported by current compiler.
#endif*/

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
/* ///////////////////////////////////////////////////////////////////////
 * Iteration Method 
 */
template < e_umax_int_t N, e_umax_int_t R >
struct factorial_impl
{
	/* In order to decrease the number of instaniation */
	typedef typename_type_k if_<
								(N > 0), 
								factorial_impl< N - 1, N * R >, 
								umax_int_<R>
								>::type result_t;

	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = result_t::value);

};
/* VECTORC: need partial specialization */
#	if defined(EXTL_COMPILER_IS_VECTORC) && \
		defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT)
template < e_umax_int_t R >
struct factorial_impl<0, R>
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = R);
};
#	endif
/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_END_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
/*!\brief: factorial class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t N >
struct factorial
	: EXTL_NS_DETAIL(factorial_impl)< N, 1 >
{
};
#else
/*!\brief: factorial class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t N >
struct factorial
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = N * factorial<N-1>::value);
};
EXTL_TEMPLATE_SPECIALISATION
struct factorial<0>
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = 1);
};
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#ifdef EXTL_MPL_MATH_FACTORIAL_TEST_ENABLE
#	include "unit_test/factorial_test.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_SUPPORT */
/* //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_FACTORIAL_H */
/* //////////////////////////////////////////////////////////////////// */
