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

#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_TEST_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../synch.h"

#ifdef EXTL_SYNCH_LOCK_TEST_ENABLE
#	include "event_lock_test.h"
#	include "mutex_lock_test.h"
#	include "semaphore_lock_test.h"
#	include "critical_section_lock_test.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

