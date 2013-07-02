/* ///////////////////////////////////////////////////////////////////////
 * File:		scoped_lock_test.h		
 *
 * Created:		08.03.20					
 * Updated:		09.01.12
 *
 * Brief:		Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_SYNCH_SCOPED_LOCK_TEST_H
#define EXTL_SYNCH_SCOPED_LOCK_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(scoped_lock_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int scoped_lock_test()
{
	null_lock lock1;

	{
		scoped_lock<null_lock> scoped_lock1(lock1);
		EXTL_ASSERT(scoped_lock1.is_locked());
	}

	EXTL_ASSERT(!lock1.is_locked());
	return 0;
}
int scoped_lock_test_ret = scoped_lock_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(scoped_lock_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_SCOPED_LOCK_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

