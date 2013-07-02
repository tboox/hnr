/* ///////////////////////////////////////////////////////////////////////
 * File:		test.h		
 *
 * Created:		08.11.24			
 * Updated:		08.12.24
 *
 * Brief:		The String Library Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_TEST_H
#define EXTL_STRING_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../string.h"

#ifdef EXTL_STRING_ATTACHED_STRING_TEST_ENABLE
#	include "attached_string_test.h"
#endif

#ifdef EXTL_STRING_SCOPED_STRING_TEST_ENABLE
#	include "scoped_string_test.h"
#endif

#ifdef EXTL_STRING_STACK_STRING_TEST_ENABLE
#	include "stack_string_test.h"
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

