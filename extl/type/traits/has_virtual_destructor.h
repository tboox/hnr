/* ///////////////////////////////////////////////////////////////////////
 * File:		has_virtual_destructor.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: has_virtual_destructor traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTORY_H
#define EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTORY_H

#ifndef EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_SUPPORT
#	error extl::has_virtual_destructor is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_HAVE_VIRTUAL_DESTRUCTOR(type)		EXTL_MUST_BE_(has_virtual_destructor, type)
#define EXTL_MUST_NOT_HAVE_VIRTUAL_DESTRUCTOR(type)	EXTL_MUST_NOT_BE_(has_virtual_destructor, type)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

EXTL_BOOL_TRAIT_DEF_1(has_virtual_destructor, EXTL_HAS_VIRTUAL_DESTRUCTOR_(T))

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/has_virtual_destructor_test.h"
#	endif
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTORY_H */
/* //////////////////////////////////////////////////////////////////// */
