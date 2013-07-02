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
#ifndef EXTL_WIN_SYNCH_MUTEX_LOCK_TEST_H
#define EXTL_WIN_SYNCH_MUTEX_LOCK_TEST_H

#ifndef EXTL_WIN_SYNCH_MUTEX_LOCK_H
#	error This file must be included of mutex_lock.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * detail namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

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
 * detail namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_MUTEX_LOCK_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

