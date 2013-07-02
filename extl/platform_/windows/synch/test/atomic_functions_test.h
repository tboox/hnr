/* ///////////////////////////////////////////////////////////////////////
 * File:		atomic_functions_test.h		
 *
 * Created:		08.03.20				
 * Updated:		08.05.06
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_ATOMIC_FUNCTIONS_TEST_H
#define EXTL_WIN_SYNCH_ATOMIC_FUNCTIONS_TEST_H

#ifndef EXTL_WIN_SYNCH_ATOMIC_FUNCTIONS_H
#	error This file must be included of atomic_functions.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * detail namespace
 */
EXTL_UNIT_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct atomic_functions_test
{
	atomic_functions_test()
	{
		e_atomic_int_t	a = 10;
		EXTL_ASSERT(atomic_preinc(&a) == 11);
		EXTL_ASSERT(atomic_predec(&a) == 10);

		EXTL_ASSERT(atomic_postdec(&a) == 10);
		EXTL_ASSERT(atomic_postinc(&a) == 9);
		
		EXTL_ASSERT(atomic_write(&a, 5) == 10);
		EXTL_ASSERT(atomic_read(&a) == 5);
	}
};

atomic_functions_test g_atomic_functions_test;
/* ///////////////////////////////////////////////////////////////////////
 * detail namespace
 */
EXTL_UNIT_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_ATOMIC_FUNCTIONS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

