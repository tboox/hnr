/* ///////////////////////////////////////////////////////////////////////
 * File:		test.h		
 *
 * Created:		08.11.24			
 * Updated:		08.11.24
 *
 * Brief:		The Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WINDOWS_COUNTER_TEST_H
#define EXTL_PLATFORM_WINDOWS_COUNTER_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../counter.h"

#ifdef EXTL_WINDOWS_COUNTER_TEST_ENABLE

#	include "highperformance_counter_test.h"
#	include "multimedia_counter_test.h"
#	include "processtimes_counter_test.h"
#	include "systemtime_counter_test.h"
#	include "tick_counter_test.h"

#	ifdef EXTL_WINDOWS_COUNTER_RDTSC_COUNTER_SUPPORT
#		include "rdtsc_counter_test.h"
#	endif
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_COUNTER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

