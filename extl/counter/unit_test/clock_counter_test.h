/* ///////////////////////////////////////////////////////////////////////
 * File:		clock_counter_test.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CLOCK_COUNTER_TEST_H
#define EXTL_CLOCK_COUNTER_TEST_H

#ifndef EXTL_CLOCK_COUNTER_H
#	error This file must be included of clock_counter.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct clock_counter_test
{
	clock_counter_test()
	{
		clock_counter counter;
		counter.begin();
		Sleep(100);
		counter.end();
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("clock_counter Test(100ms):\n"));
		EXTL_TEST_TRACE(_T("Count:   %u"), static_cast<e_uint32_t>(counter.count()));
		EXTL_TEST_TRACE(_T("Seconds: %u"), static_cast<e_uint32_t>(counter.seconds()));
		EXTL_TEST_TRACE(_T("MS:      %u"), static_cast<e_uint32_t>(counter.ms()));
		EXTL_TEST_TRACE(_T("US:      %u"), static_cast<e_uint32_t>(counter.us()));
	}
};

clock_counter_test g_clock_counter_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CLOCK_COUNTER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

