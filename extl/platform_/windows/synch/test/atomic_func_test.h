/* ///////////////////////////////////////////////////////////////////////
 * File:		atomic_func_test.h		
 *
 * Created:		08.03.20				
 * Updated:		09.01.15
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WINDOWS_SYNCH_ATOMIC_FUNCTIONS_TEST_H
#define EXTL_WINDOWS_SYNCH_ATOMIC_FUNCTIONS_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(atomic_func_lock_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct atomic_func_test
{
	atomic_func_test()
	{
		e_atomic_t a = 10;
		EXTL_ASSERT(atomic_preinc(&a) == 11);
		EXTL_ASSERT(atomic_predec(&a) == 10);

		EXTL_ASSERT(atomic_postdec(&a) == 10);
		EXTL_ASSERT(atomic_postinc(&a) == 9);
		
		EXTL_ASSERT(atomic_write(&a, 5) == 10);
		EXTL_ASSERT(atomic_read(&a) == 5);
	}
};

atomic_func_test g_atomic_func_test;

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(atomic_func_lock_test)
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WINDOWS_SYNCH_ATOMIC_FUNCTIONS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

