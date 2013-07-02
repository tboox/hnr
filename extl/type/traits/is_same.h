/* ///////////////////////////////////////////////////////////////////////
 * File:		is_same.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_same traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_SAME_H
#define EXTL_TYPE_TRAITS_IS_SAME_H

#ifndef EXTL_TYPE_TRAITS_IS_SAME_SUPPORT
#	error extl::is_same is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_SAME(type1, type2)			EXTL_MUST_BE_2_(is_same, type1, type2)
#define EXTL_MUST_BE_CV_SAME(type1, type2)		EXTL_MUST_BE_CV_2_(is_same, type1, type2)

#define EXTL_MUST_NOT_BE_SAME(type1, type2)		EXTL_MUST_NOT_BE_2_(is_same, type1, type2)
#define EXTL_MUST_NOT_BE_CV_SAME(type1, type2)	EXTL_MUST_NOT_BE_CV_2_(is_same, type1, type2)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) && \
			!defined(EXTL_COMPILER_IS_VECTORC) // not using partial specialization will generate more effect at VECTORC 2.1.7

	EXTL_BOOL_TRAIT_DEF_2(is_same, e_false_v)
	EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k T, is_same, T, T, e_true_v)

#	else
	template< typename_param_k T1 >
	struct is_same_impl
	{
		template<typename_param_k T2>  
		struct result
		{ 
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
		};

		EXTL_TEMPLATE_SPECIALISATION            
		struct result<T1> 
		{ 
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
		};
	};

	EXTL_BOOL_TRAIT_DEF_2(is_same,is_same_impl<T1>::template_qual_k result<T2>::value)

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_same_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_SAME_H */
/* //////////////////////////////////////////////////////////////////// */
