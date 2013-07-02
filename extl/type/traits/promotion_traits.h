/* ///////////////////////////////////////////////////////////////////////
 * File:		promotion_traits.h		
 *
 * Created:		08.03.28					
 * Updated:		08.07.09
 *
 * Brief: promotion_traits traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_H
#define EXTL_TYPE_TRAITS_PROMOTION_TRAITS_H

#ifndef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT
#	error extl::promotion_traits is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IF_SUPPORT
#	include "if_.h"
#endif

#include "is_void.h"
#include "logical_op.h"
#include "is_int.h"
#include "is_float.h"
#include "is_arithmetic.h"

#ifdef EXTL_TYPE_TRAITS_IS_SAME_SUPPORT
#	include "is_same.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* ///////////////////////////////////////////////////////////////////////
 * ::detail namespace 
 */
EXTL_DETAIL_BEGIN_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#if defined(EXTL_COMPILER_IS_VECTORC) /* VECTORC needn't brackets */
template < typename_param_k T1, typename_param_k T2 >
struct promotion_traits_same_size_helper
{
	typedef typename_type_k if_3_	<	op_and	<	is_float<T1>::value
												,	is_int<T2>::value
												>::value,
										op_and	<	is_int<T1>::value
												,	is_float<T2>::value
												>::value,
										op_and	<	is_int<T1>::value
												,	is_int<T2>::value
												>::value
									,	T1
									,	T2
									,	int
									,	void
									>::type	type;
};

template < typename_param_k T1, typename_param_k T2 >
struct promotion_traits_impl
{
	typedef typename_type_k if_2_	<	is_same<T1, T2>::value
									,	op_and	<	is_arithmetic<T1>::value
												,	is_arithmetic<T2>::value
												>::value
									,	T1	/* T1 == T2 */
									,	typename_type_k if_2_	<	(sizeof(T1) == sizeof(T2))
																,	(sizeof(T1) > sizeof(T2))
																,	typename_type_k promotion_traits_same_size_helper<T1, T2>::type
																,	T1
																,	T2
																>::type
									,	void
									>::type	type;
};
#else /* BORLAND need brackets */
template < typename_param_k T1, typename_param_k T2 >
struct promotion_traits_same_size_helper
{
	typedef typename_type_k if_3_	<	(op_and	<	(is_float<T1>::value)
												,	(is_int<T2>::value)
												,	EXTL_OP_AND_DEF_ARG_2
												>::value)
									,	(op_and	<	(is_int<T1>::value)
												,	(is_float<T2>::value)
												,	EXTL_OP_AND_DEF_ARG_2
												>::value)
									,	(op_and	<	(is_int<T1>::value)
												,	(is_int<T2>::value)
												,	EXTL_OP_AND_DEF_ARG_2
												>::value)
									,	T1
									,	T2
									,	int
									,	void
									>::type	type;
};

template < typename_param_k T1, typename_param_k T2 >
struct promotion_traits_impl
{
	typedef typename_type_k if_2_	<	(is_same<T1, T2>::value)
									,	(op_and	<	(is_arithmetic<T1>::value)
												,	(is_arithmetic<T2>::value)
												,	EXTL_OP_AND_DEF_ARG_2
												>::value)
									,	T1	/* T1 == T2 */
									,	typename_type_k if_2_	<	(sizeof(T1) == sizeof(T2))
																,	(sizeof(T1) > sizeof(T2))
																,	typename_type_k promotion_traits_same_size_helper<T1, T2>::type
																,	T1
																,	T2
																>::type
									,	void
								>::type	type;
};
#endif /* EXTL_COMPILER_IS_VECTORC */

EXTL_TYPE_TRAIT_SPEC_2(promotion_traits_impl, void, void, void)
/* ///////////////////////////////////////////////////////////////////////
 * ::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE 
/* //////////////////////////////////////////////////////////////////// */
template < typename_param_k T1, typename_param_k T2 >
struct promotion_traits
	: EXTL_NS_DETAIL(promotion_traits_impl)<T1, T2>
{
};

template < typename_param_k T1, typename_param_k T2 >
struct promotion_traits_2_
	: promotion_traits<T1, T2>
{
};

template < typename_param_k T1, typename_param_k T2, typename_param_k T3 >
struct promotion_traits_3_
{
	typedef typename_type_k promotion_traits_2_	<	typename_type_k promotion_traits_2_<T1, T2>::type 
												,	T3
												>::type type;
};

template < typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4 >
struct promotion_traits_4_
{
	typedef typename_type_k promotion_traits_2_	<	typename_type_k promotion_traits_2_<T1, T2>::type 
												,	typename_type_k promotion_traits_2_<T3, T4>::type
												>::type type;
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/promotion_traits_test.h"
#	endif

#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_TRAITS_PROMOTION_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
