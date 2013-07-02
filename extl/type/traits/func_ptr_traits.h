/* ///////////////////////////////////////////////////////////////////////
 * File:		func_ptr_traits.h		
 *
 * Created:		08.07.16					
 * Updated:		08.07.16
 *
 * Brief: func_ptr_traits traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_H
#define EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_H

#ifndef EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_SUPPORT
#	error extl::func_ptr_traits is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_FUNC_PTR_SUPPORT)
#	include "detail/func_ptr_traits_impl.h"
#elif defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)	// for vc6.0
#	include "detail/func_ptr_traits_impl_2.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

template <typename_param_k FP>
struct func_ptr_traits 
	: EXTL_NS_DETAIL(func_ptr_traits_impl)<FP>
{
};
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#	include "unit_test/func_ptr_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
