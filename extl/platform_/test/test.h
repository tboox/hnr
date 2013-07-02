/* ///////////////////////////////////////////////////////////////////////
 * File:		test.h		
 *
 * Created:		08.11.23					
 * Updated:		08.11.23	
 *
 * Brief:		The Platform Library Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_TEST_H
#define EXTL_PLATFORM_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

// the synchronization library 
#include "../synch/test/test.h"

// the counter library 
#include "../counter/test/test.h"

/* ///////////////////////////////////////////////////////////////////////
 * Unix/Windows Testing
 */
#if defined(EXTL_PLATFORM_IS_UNIX)
#	include "../unix/test/test.h"
#elif defined(EXTL_PLATFORM_IS_WINDOWS)
#	include "../windows/test/test.h"
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_PLATFORM_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
