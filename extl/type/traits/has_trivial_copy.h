/* ///////////////////////////////////////////////////////////////////////
 * File:		has_trivial_copy.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: has_trivial_copy traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_HAS_TRIVIAL_COPYY_H
#define EXTL_TYPE_TRAITS_HAS_TRIVIAL_COPYY_H

#ifndef EXTL_TYPE_TRAITS_HAS_TRIVIAL_COPY_SUPPORT
#	error extl::has_trivial_copy is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"
#include "is_volatile.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "is_pod.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_HAVE_TRIVIAL_COPY(type)		EXTL_MUST_BE_(has_trivial_copy, type)
#define EXTL_MUST_NOT_HAVE_TRIVIAL_COPY(type)	EXTL_MUST_NOT_BE_(has_trivial_copy, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(has_trivial_copy, (op_and	<	(op_or	<	(is_pod<T>::value)
															,	EXTL_HAS_TRIVIAL_COPY_(T)
															>::value)
												,	(op_not< (is_volatile<T>::value) >::value)
												>::value))

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/has_trivial_copy_test.h"
#	endif
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_HAS_TRIVIAL_COPYY_H */
/* //////////////////////////////////////////////////////////////////// */
