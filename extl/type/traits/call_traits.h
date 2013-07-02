/* ///////////////////////////////////////////////////////////////////////
 * File:		call_traits.h		
 *
 * Created:		08.07.21				
 * Updated:		08.07.21
 *
 * Brief: for passing function parameters and returning value by reference
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_TYPE_TRAITS_CALL_TRAITS_H
#define EXTL_TYPE_TRAITS_CALL_TRAITS_H

#ifndef EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#	error extl::call_traits is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IF_SUPPORT
#	include "if_.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#	include "is_scalar.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_CONST_REF_SUPPORT
#	include "add_const_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#	include "add_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_CONST_SUPPORT
#	include "remove_const.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* note: add_const traits will not add const-qualified if T is non-const refernce type (T&)
 * Because T const& cannot be converted to T& implicitly .
 * e.g.
	void func(int&);
	void func2(int const& a){ func(a); } - compile error
	void func2(call_traits<int&>::param_type a){ func(a); } - compile successfully
 */
template <typename_param_k T>
struct call_traits
{
	typedef T										value_type;
	typedef typename_type_k add_ref	<	typename_type_k remove_const<T>::type
									>::type			reference;
	typedef typename_type_k add_const_ref<T>::type	const_reference;

	// Passing by value if T is scalar type
#if defined(EXTL_TYPE_TRAITS_IF_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT) && \
			!EXTL_WORKAROUND_BORLAND(==, 0x551)
	typedef typename_type_k if_	<	(is_scalar<T>::value)
								,	value_type
								,	const_reference
								>::type				param_type;
	
#else
	typedef const_reference							param_type;
#endif

};

EXTL_TEMPLATE_SPECIALISATION
struct call_traits<e_null_t>
{
	typedef e_null_t			value_type;
	typedef e_null_t			reference;
	typedef e_null_t			const_reference;
	typedef e_null_t			param_type;
};

EXTL_TEMPLATE_SPECIALISATION
struct call_traits<void>
{
	typedef void					value_type;
	typedef void					reference;
	typedef void const				const_reference;
	typedef void					param_type;
};
#ifdef EXTL_CV_VOID_SPEC_SUPPORT	
EXTL_TEMPLATE_SPECIALISATION
struct call_traits<void const>
{
	typedef void const				value_type;
	typedef void					reference;
	typedef void const				const_reference;
	typedef void const				param_type;
};
EXTL_TEMPLATE_SPECIALISATION
struct call_traits<void volatile>
{
	typedef void volatile			value_type;
	typedef void volatile			reference;
	typedef void const volatile		const_reference;
	typedef void volatile			param_type;
};
EXTL_TEMPLATE_SPECIALISATION
struct call_traits<void const volatile>
{
	typedef void const volatile		value_type;
	typedef void volatile			reference;
	typedef void const volatile		const_reference;
	typedef void const volatile		param_type;
};
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#	include "unit_test/call_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_CALL_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
