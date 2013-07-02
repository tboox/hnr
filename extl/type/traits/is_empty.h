/* ///////////////////////////////////////////////////////////////////////
 * File:		is_empty.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_empty traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_EMPTY_H
#define EXTL_TYPE_TRAITS_IS_EMPTY_H

#ifndef EXTL_TYPE_TRAITS_IS_EMPTY_SUPPORT
#	error extl::is_empty is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#	include "is_class.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_EMPTY(type)			EXTL_MUST_BE_(is_empty, type)
#define EXTL_MUST_BE_CV_EMPTY(type)			EXTL_MUST_BE_CV_(is_empty, type)

#define EXTL_MUST_NOT_BE_EMPTY(type)		EXTL_MUST_NOT_BE_(is_empty, type)
#define EXTL_MUST_NOT_BE_CV_EMPTY(type)		EXTL_MUST_NOT_BE_CV_(is_empty, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
struct is_empty_helper1 { e_byte_t padding[256]; };

template < typename_param_k T >
struct is_empty_helper2 : public T
{
	is_empty_helper2(); 
	e_byte_t padding[256];
private:
	is_empty_helper2(is_empty_helper2 const&);
	is_empty_helper2& operator=(is_empty_helper2 const&);
};

template < e_bool_t is_class >
struct is_empty_selector
{
	template < typename_param_k T >
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct is_empty_selector< e_true_v >
{
	template < typename_param_k T >
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(is_empty_helper2<T>) == sizeof(is_empty_helper1)));
	};
};

template < typename_param_k T >
struct is_empty_impl
	: is_empty_selector< (is_class<T>::value) >::template_qual_k result<T>
{
};

EXTL_BOOL_TRAIT_DEF_1(is_empty, (op_or	<	(is_empty_impl< T >::value)
										,	EXTL_IS_EMPTY_(T)
										>::value))

EXTL_BOOL_TRAIT_SPEC_1(is_empty, void, e_false_v)
#	ifdef EXTL_CV_VOID_SPEC_SUPPORT	
	EXTL_BOOL_TRAIT_SPEC_1(is_empty, void const, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_empty, void volatile, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_empty, void const volatile, e_false_v)
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_empty_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_EMPTY_H */
/* //////////////////////////////////////////////////////////////////// */
