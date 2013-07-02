/* ///////////////////////////////////////////////////////////////////////
 * File:		add_volatile.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: add volatile-qualified traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_ADD_VOLATILE_H
#define EXTL_TYPE_TRAITS_ADD_VOLATILE_H

#ifndef EXTL_TYPE_TRAITS_ADD_VOLATILE_SUPPORT
#	error extl::add_volatile is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	include "is_ref.h"
#endif

#ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#	ifdef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
#		include "is_volatile.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_ADD_VOLATILE(src_type)	EXTL_MODIFY_TYPE(add_volatile, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
	EXTL_TYPE_TRAIT_DEF_1(add_volatile, T volatile)

	// note: Cannot add volatile-qualified if T is reference
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, add_volatile, T&, T&)
#	else
	template < e_bool_t is_ref >
	struct add_volatile_helper
	{
		template < typename_param_k T >
		struct result
		{
			typedef T type;
		};
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct add_volatile_helper< e_false_v >
	{
		template < typename_param_k T >
		struct result
		{
			typedef T volatile type;
		};
	};

	template < typename_param_k T >
	struct add_volatile_impl
		: add_volatile_helper< (is_ref<T>::value) >::template_qual_k result<T>
	{
	};

	EXTL_TYPE_TRAIT_DEF_1(add_volatile, typename_type_k add_volatile_impl<T>::type)

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/add_volatile_test.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_ADD_VOLATILE_H */
/* //////////////////////////////////////////////////////////////////// */
