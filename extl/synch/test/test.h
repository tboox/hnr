/* ///////////////////////////////////////////////////////////////////////
 * File:		test.h		
 *
 * Created:		08.11.24			
 * Updated:		08.11.24
 *
 * Brief:		The Synchronization Library Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_SYNCH_TEST_H
#define EXTL_SYNCH_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../synch.h"

#ifdef EXTL_SYNCH_LOCK_TEST_ENABLE
#	include "scoped_lock_test.h"
#	include "null_lock_test.h"
#	include "atomic_traits_test.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

