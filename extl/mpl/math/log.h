/* ///////////////////////////////////////////////////////////////////////
 * File:		log.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief: Caculate N = log<P, R> => R = P^N
 *
 * Note: range from 0 to 1000
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_LOG_H
#define EXTL_MPL_MATH_LOG_H

/*!\file log.h
 * \brief Caculate N = log<P, R> => R = P^N
 * 
 * Note: range from 0 to 1000
 */

#ifndef EXTL_MPL_MATH_LOG_SUPPORT
#	error extl::log is not supported by current compiler.
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

template < e_umax_int_t L, e_umax_int_t V, e_umax_int_t I, e_umax_int_t P >
struct log_impl
{
	/* In order to decrease the number of instaniation and do not need partial specialization */
	typedef typename_type_k if_2_<	(P > V)
								,	(P < V)
								,	typename_type_k umax_int_<I>::prior
								,	log_impl< L, V, I + 1, L * P >
								,	umax_int_<I>
								>::type result_t;

	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = result_t::value);
};

/* VECTORC: need partial specialization */
#	if defined(EXTL_COMPILER_IS_VECTORC) && \
		defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT)
template < e_umax_int_t L, e_umax_int_t V, e_umax_int_t I >
struct log_impl<L, V, I, V>
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = I);
};
#	endif

/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_END_NAMESPACE /* ::extl::mpl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */
/*!\brief: log class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t L, e_umax_int_t V >
struct log
	: EXTL_NS_DETAIL(log_impl)< L, V, 0, 1 >
{
};
/*!\brief: log_2 class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t V >
struct log_2
	: EXTL_NS_DETAIL(log_impl)< 2, V, 0, 1 >
{
};
/*!\brief: log_10 class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t V >
struct log_10
	: EXTL_NS_DETAIL(log_impl)< 10, V, 0, 1 >
{
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#ifdef EXTL_MPL_MATH_LOG_TEST_ENABLE
#	include "unit_test/log_test.h"
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
#endif /* EXTL_MPL_MATH_LOG_H */
/* //////////////////////////////////////////////////////////////////// */
