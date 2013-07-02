/* ///////////////////////////////////////////////////////////////////////
 * File:		event_lock_test.h		
 *
 * Created:		08.03.20				
 * Updated:		08.05.06
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WINDOWS_SYNCH_EVENT_LOCK_TEST_H
#define EXTL_WINDOWS_SYNCH_EVENT_LOCK_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(event_lock_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct event_lock_test
{
	event_lock_test()
	{
		{
			event_lock lock_test;

			lock_test.lock();
			EXTL_ASSERT(lock_test.is_locked());
			lock_test.unlock();
		}
	}
};

event_lock_test g_event_lock_test;

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(event_lock_test)
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WINDOWS_SYNCH_EVENT_LOCK_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

