/* ///////////////////////////////////////////////////////////////////////
 * File:		mutex_lock_test.h		
 *
 * Created:		08.03.20				
 * Updated:		08.05.06
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WINDOWS_SYNCH_MUTEX_LOCK_TEST_H
#define EXTL_WINDOWS_SYNCH_MUTEX_LOCK_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(mutex_lock_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct mutex_lock_test
{
	mutex_lock_test()
	{
		{
			mutex_lock lock_test;

			lock_test.lock();
			EXTL_ASSERT(lock_test.is_locked());
			lock_test.unlock();
		}
	}
};

mutex_lock_test g_mutex_lock_test;

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(mutex_lock_test)
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WINDOWS_SYNCH_MUTEX_LOCK_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

