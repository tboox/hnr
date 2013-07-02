/* ///////////////////////////////////////////////////////////////////////
 * File:		add_cv.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: add cv-qualified traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_TYPE_TRAITS_ADD_CV_H
#define EXTL_TYPE_TRAITS_ADD_CV_H

#ifndef EXTL_TYPE_TRAITS_ADD_CV_SUPPORT
#	error extl::add_cv is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	include "is_ref.h"
#endif

#ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#	ifdef EXTL_TYPE_TRAITS_IS_CV_SUPPORT
#		include "is_cv.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_ADD_CV(src_type)	EXTL_MODIFY_TYPE(add_cv, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
	EXTL_TYPE_TRAIT_DEF_1(add_cv, T const volatile)

	// note: Cannot add cv-qualified if T is reference
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, add_cv, T&, T&)
#	else
	template < e_bool_t is_ref >
	struct add_cv_helper
	{
		template < typename_param_k T >
		struct result
		{
			typedef T type;
		};
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct add_cv_helper< e_false_v >
	{
		template < typename_param_k T >
		struct result
		{
			typedef T const volatile type;
		};
	};

	template < typename_param_k T >
	struct add_cv_impl
		: add_cv_helper< (is_ref<T>::value) >::template_qual_k result<T>
	{
	};

	EXTL_TYPE_TRAIT_DEF_1(add_cv, typename_type_k add_cv_impl<T>::type)

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/add_cv_test.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_ADD_CV_H */
/* //////////////////////////////////////////////////////////////////// */
