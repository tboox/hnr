/* ///////////////////////////////////////////////////////////////////////
 * File:		has_trivial_destructor.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: has_trivial_destructor traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTORY_H
#define EXTL_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTORY_H

#ifndef EXTL_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTOR_SUPPORT
#	error extl::has_trivial_destructor is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "is_pod.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_HAVE_TRIVIAL_DESTRUCTOR(type)		EXTL_MUST_BE_(has_trivial_destructor, type)
#define EXTL_MUST_NOT_HAVE_TRIVIAL_DESTRUCTOR(type)	EXTL_MUST_NOT_BE_(has_trivial_destructor, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(has_trivial_destructor, (op_or<	(is_pod<T>::value)
													,	EXTL_HAS_TRIVIAL_DESTRUCTOR_(T)
													>::value))

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/has_trivial_destructor_test.h"
#	endif
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTORY_H */
/* //////////////////////////////////////////////////////////////////// */
