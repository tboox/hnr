/* ///////////////////////////////////////////////////////////////////////
 * File:		is_enum.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_enum traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_ENUM_H
#define EXTL_TYPE_TRAITS_IS_ENUM_H

#ifndef EXTL_TYPE_TRAITS_IS_ENUM_SUPPORT
#	error extl::is_enum is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_arithmetic.h"

#ifdef EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_SUPPORT
#	include "is_class_or_union.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
#	include "is_convertible.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	include "is_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	include "is_array.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#	include "add_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT
#	include "is_func.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_ENUM(type)			EXTL_MUST_BE_(is_enum, type)
#define EXTL_MUST_BE_CV_ENUM(type)		EXTL_MUST_BE_CV_(is_enum, type)

#define EXTL_MUST_NOT_BE_ENUM(type)		EXTL_MUST_NOT_BE_(is_enum, type)
#define EXTL_MUST_NOT_BE_CV_ENUM(type)	EXTL_MUST_NOT_BE_CV_(is_enum, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */

struct int_convertible
{
    int_convertible(int);
};

template < e_bool_t is_arithmetic_or_ref >
struct is_enum_selector
{
    template < typename_param_k T >
	struct result
    {
        EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
    };
};

EXTL_TEMPLATE_SPECIALISATION
struct is_enum_selector< e_false_v >
{
    template < typename_param_k T >
	struct result
    {
	#ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
		typedef typename_type_k add_ref<T>::type ref_t;
	#else
		typedef T ref_t;
	#endif
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = 
			(is_convertible< ref_t, int_convertible >::value));
    };
};

template < typename_param_k T > 
struct is_enum_helper
{
#if defined(EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_SUPPORT) && \
				defined(EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT) 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_or	<	(is_arithmetic<T>::value)
														,	(is_ref<T>::value)
														,	(is_func<T>::value)
														,	(is_class_or_union<T>::value)
														,	(is_array<T>::value)
														>::value));
#elif defined(EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT) 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_or	<	(is_arithmetic<T>::value)
														,	(is_ref<T>::value)
														,	(is_func<T>::value)
														,	(is_array<T>::value)
														>::value));
#else
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_or	<	(is_arithmetic<T>::value)
														,	(is_ref<T>::value)
														,	(is_array<T>::value)
														>::value));
#endif
};

template < typename_param_k T > 
struct is_enum_impl
	: is_enum_selector<(is_enum_helper<T>::value)>::template_qual_k result<T>
{
};

EXTL_BOOL_TRAIT_DEF_1(is_enum, (is_enum_impl<T>::value))

EXTL_BOOL_TRAIT_SPEC_1(is_enum, void, e_false_v)
#	ifdef EXTL_CV_VOID_SPEC_SUPPORT	
	EXTL_BOOL_TRAIT_SPEC_1(is_enum, void const, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_enum, void volatile, e_false_v)
	EXTL_BOOL_TRAIT_SPEC_1(is_enum, void const volatile, e_false_v)
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_enum_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_ENUM_H */
/* //////////////////////////////////////////////////////////////////// */
