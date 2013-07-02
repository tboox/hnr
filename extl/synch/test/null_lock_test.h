/* ///////////////////////////////////////////////////////////////////////
 * File:		null_lock_test.h		
 *
 * Created:		08.03.20					
 * Updated:		09.01.12
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_SYNCH_NULL_LOCK_TEST_H
#define EXTL_SYNCH_NULL_LOCK_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(null_lock_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int null_lock_test()
{
	EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
	EXTL_TEST_TRACE(_T("null_lock Test:\n"));

	{
		null_lock lock_test;

		lock_test.lock();
		EXTL_ASSERT(lock_test.is_locked());
		lock_test.unlock();
	}

	EXTL_TRY
		lock_test.lock();
		lock_test.lock();
	EXTL_CATCH (lock_error &e)
		EXTL_TEST_TRACEA("Error Reason:%s",e.what());
	EXTL_CATCH_END

	return 0;
}
int null_lock_test_ret = null_lock_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(null_lock_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_NULL_LOCK_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

