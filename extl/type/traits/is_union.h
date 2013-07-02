/* ///////////////////////////////////////////////////////////////////////
 * File:		is_union.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_union traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_UNION_H
#define EXTL_TYPE_TRAITS_IS_UNION_H

#ifndef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT
#	error extl::is_union is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	include "remove_cv.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_UNION(type)		EXTL_MUST_BE_(is_union, type)
#define EXTL_MUST_BE_CV_UNION(type)		EXTL_MUST_BE_CV_(is_union, type)

#define EXTL_MUST_NOT_BE_UNION(type)	EXTL_MUST_NOT_BE_(is_union, type)
#define EXTL_MUST_NOT_BE_CV_UNION(type)	EXTL_MUST_NOT_BE_CV_(is_union, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

#	ifdef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT

#		ifdef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
		EXTL_BOOL_TRAIT_DEF_1(is_union, EXTL_IS_UNION_(typename_type_k remove_cv<T>::type))
#		else
		EXTL_BOOL_TRAIT_DEF_1(is_union, EXTL_IS_UNION_(T))
#		endif
#	else
#		error extl::is_union is not supported by current compiler.
#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_union_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_UNION_H */
/* //////////////////////////////////////////////////////////////////// */
