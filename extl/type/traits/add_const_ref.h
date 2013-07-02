/* ///////////////////////////////////////////////////////////////////////
 * File:		add_const_ref.h		
 *
 * Created:		08.07.15					
 * Updated:		08.07.15
 *
 * Brief: add const-reference traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_ADD_CONST_REF_H
#define EXTL_TYPE_TRAITS_ADD_CONST_REF_H

#ifndef EXTL_TYPE_TRAITS_ADD_CONST_REF_SUPPORT
#	error extl::add_const_ref is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#	include "add_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT
#	include "add_const.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_ADD_CONST_REF(src_type)	EXTL_MODIFY_TYPE(add_const_ref, src_type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
	EXTL_TYPE_TRAIT_DEF_1(add_const_ref, T const&)
	EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(typename_param_k T, add_const_ref, T&, T&)
#else
	EXTL_TYPE_TRAIT_DEF_1(add_const_ref, typename_type_k add_ref< typename_type_k add_const<T>::type >::type)
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#	include "unit_test/add_const_ref_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_ADD_CONST_REF_H */
/* //////////////////////////////////////////////////////////////////// */
