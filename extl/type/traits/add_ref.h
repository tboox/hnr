/* ///////////////////////////////////////////////////////////////////////
 * File:		add_ref.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: add reference traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_ADD_REF_H
#define EXTL_TYPE_TRAITS_ADD_REF_H

#ifndef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#	error extl::add_ref is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	include "is_ref.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_ADD_REF(src_type)	EXTL_MODIFY_TYPE(add_ref, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT

	EXTL_TYPE_TRAIT_DEF_1(add_ref, T&)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, add_ref, T&, T&)

#	else	
	template <e_bool_t is_ref>
	struct add_ref_helper
	{
		template <typename_param_k T> struct result
		{
			typedef T& type;
		};
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct add_ref_helper<e_true_v>
	{
		template <typename_param_k T> struct result
		{
			typedef T type;
		};
	};

	template <typename_param_k T>
	struct add_ref_impl
	{
		typedef typename_type_k add_ref_helper	<	is_ref<T>::value 
												>::template_qual_k result<T>::type type;
	};

	EXTL_TYPE_TRAIT_DEF_1(add_ref, typename_type_k add_ref_impl<T>::type)

#	endif

	EXTL_TYPE_TRAIT_SPEC_1(add_ref, void, void)
#	ifdef EXTL_CV_VOID_SPEC_SUPPORT	
	EXTL_TYPE_TRAIT_SPEC_1(add_ref, void const, void const)
	EXTL_TYPE_TRAIT_SPEC_1(add_ref, void volatile, void volatile)
	EXTL_TYPE_TRAIT_SPEC_1(add_ref, void const volatile, void const volatile)
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/add_ref_test.h"
#	endif

#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_ADD_REF_H */
/* //////////////////////////////////////////////////////////////////// */
