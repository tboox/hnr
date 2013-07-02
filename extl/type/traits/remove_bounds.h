/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_bounds.h		
 *
 * Created:		08.02.07				
 * Updated:		08.07.09
 *
 * Brief: remove_bounds traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_BOUNDS_H
#define EXTL_TYPE_TRAITS_REMOVE_BOUNDS_H

#ifndef EXTL_TYPE_TRAITS_REMOVE_BOUNDS_SUPPORT
#	error extl::remove_bounds is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#	include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	include "is_array.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_BOUND_SUPPORT
#	include "remove_bound.h"
#endif

#ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#	include "is_arithmetic.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_REMOVE_BOUNDS(src_type)	EXTL_MODIFY_TYPE(remove_bounds, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
#	ifdef EXTL_TYPE_TRAITS_REMOVE_BOUND_SUPPORT
	template < typename_param_k T >
	struct remove_bounds_impl;

	template < e_bool_t is_array >
	struct remove_bounds_helper
	{
		template < typename_param_k T>
		struct result
		{
			typedef T type;
		};
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct remove_bounds_helper< e_true_v >
	{
		template < typename_param_k T>
		struct result
		{
			typedef typename_type_k remove_bound<T>::type reduced_type;
			typedef typename_type_k remove_bounds_impl<reduced_type>::type type;
		};
	};

	template < typename_param_k T >
	struct remove_bounds_impl
		: remove_bounds_helper< (is_array<T>::value) >::template_qual_k result<T>
	{
		
	};

	EXTL_TYPE_TRAIT_DEF_1(remove_bounds, typename_type_k remove_bounds_impl<T>::type)

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/remove_bounds_test.h"
#	endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_REMOVE_BOUNDS_H */
/* //////////////////////////////////////////////////////////////////// */
