/* ///////////////////////////////////////////////////////////////////////
 * File:		has_trivial_assign.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: has_trivial_assign traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_TYPE_TRAITS_HAS_TRIVIAL_ASSIGNY_H
#define EXTL_TYPE_TRAITS_HAS_TRIVIAL_ASSIGNY_H

#ifndef EXTL_TYPE_TRAITS_HAS_TRIVIAL_ASSIGN_SUPPORT
#	error extl::has_trivial_assign is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "is_pod.h"
#endif

#include "is_const.h"
#include "is_volatile.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_HAVE_TRIVIAL_ASSIGN(type)		EXTL_MUST_BE_(has_trivial_assign, type)
#define EXTL_MUST_NOT_HAVE_TRIVIAL_ASSIGN(type)	EXTL_MUST_NOT_BE_(has_trivial_assign, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(has_trivial_assign, (op_and	<	(op_or
														<	(is_pod<T>::value)
														,	EXTL_HAS_TRIVIAL_ASSIGN_(T)
														>::value)
													,	(op_not< (is_const<T>::value) >::value)
													,	(op_not< (is_volatile<T>::value) >::value)
													>::value))

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/has_trivial_assign_test.h"
#	endif
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_HAS_TRIVIAL_ASSIGNY_H */
/* //////////////////////////////////////////////////////////////////// */
