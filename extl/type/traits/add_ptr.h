/* ///////////////////////////////////////////////////////////////////////
 * File:		add_ptr.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: add pointer traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_ADD_PTR_H
#define EXTL_TYPE_TRAITS_ADD_PTR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	include "is_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
#	include "remove_ref.h"
#endif

#ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#	ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#		include "is_ptr.h"
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_ADD_PTR(src_type)	EXTL_MODIFY_TYPE(add_ptr, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
	EXTL_TYPE_TRAIT_DEF_1(add_ptr, typename_type_k remove_ref<T>::type*)
#	else	

	template < e_bool_t is_ref >
	struct add_ptr_helper
	{
		template < typename_param_k T>
		struct result
		{
			typedef T type;
		};
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct add_ptr_helper< e_false_v >
	{
		template < typename_param_k T>
		struct result
		{
			typedef T* type;
		};
	};

	template < typename_param_k T >
	struct add_ptr_impl
		: add_ptr_helper< (is_ref<T>::value) >::template_qual_k result<T>
	{
		
	};

	EXTL_TYPE_TRAIT_DEF_1(add_ptr, typename_type_k add_ptr_impl<T>::type)

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/add_ptr_test.h"
#	endif

#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_ADD_PTR_H */
/* //////////////////////////////////////////////////////////////////// */
