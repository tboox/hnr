/* ///////////////////////////////////////////////////////////////////////
 * File:		is_cv.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_cv traits - const volatile
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CV_H
#define EXTL_TYPE_TRAITS_IS_CV_H

#ifndef EXTL_TYPE_TRAITS_IS_CV_SUPPORT
#	error extl::is_cv is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
#	include "is_const.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
#	include "is_volatile.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_CV(type)		EXTL_MUST_BE_(is_cv, type)
#define EXTL_MUST_NOT_BE_CV(type)	EXTL_MUST_NOT_BE_(is_cv, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(is_cv, (op_and< (is_const<T>::value), (is_volatile<T>::value) >::value))

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_cv_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_CV_H */
/* //////////////////////////////////////////////////////////////////// */
