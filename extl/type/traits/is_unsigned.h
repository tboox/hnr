/* ///////////////////////////////////////////////////////////////////////
 * File:		is_unsigned.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_unsigned traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_UNSIGNED_H
#define EXTL_TYPE_TRAITS_IS_UNSIGNED_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_int.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_UNSIGNED(type)			EXTL_MUST_BE_(is_unsigned, type)
#define EXTL_MUST_NOT_BE_UNSIGNED(type)		EXTL_MUST_NOT_BE_(is_unsigned, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) && \
			!EXTL_WORKAROUND_BORLAND(==, 0x0564)
	template < e_bool_t is_int >
	struct is_unsigned_helper
	{
		template < typename_param_k T >
		struct result
		{
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
		};
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct is_unsigned_helper<e_true_v>
	{
		template < typename_param_k T >
		struct result
		{
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (static_cast<T>(-1) > 0));
		};
	};

	template < typename_param_k T >
	struct is_unsigned_impl
		: is_unsigned_helper< (is_int<T>::value) >::template_qual_k result<T>
	{
	};

	EXTL_BOOL_TRAIT_DEF_1(is_unsigned, is_unsigned_impl<T>::value)

#	else

	EXTL_BOOL_TRAIT_DEF_1(is_unsigned, e_false_v)

	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned char, e_true_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned short, e_true_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned int, e_true_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned long, e_true_v)

	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed char, e_false_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed short, e_false_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed int, e_false_v)
	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed long, e_false_v)

	EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, char, e_false_v)

#		ifdef EXTL_NATIVE_BOOL_SUPPORT
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, bool, e_false_v)
#		endif

#		ifdef EXTL_NATIVE_WCHAR_T_SUPPORT
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, wchar_t, e_true_v)
#		endif

#		ifdef EXTL_08BIT_INT_IS___int8
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned __int8, e_true_v)
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed __int8, e_false_v)
#		endif

#		ifdef EXTL_16BIT_INT_IS___int16
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned __int16, e_true_v)
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed __int16, e_false_v)
#		endif

#		ifdef EXTL_32BIT_INT_IS___int32
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned __int32, e_true_v)
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed __int32, e_false_v)
#		endif

#		ifdef EXTL_64BIT_INT_IS___int64
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned __int64, e_true_v)
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed __int64, e_false_v)
#		endif

#		ifdef EXTL_64BIT_INT_IS_long_long
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, unsigned long long, e_true_v)
		EXTL_BOOL_TRAIT_CV_SPEC_1(is_unsigned, signed long long, e_false_v)
#		endif
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_unsigned_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_UNSIGNED_H */
/* //////////////////////////////////////////////////////////////////// */
