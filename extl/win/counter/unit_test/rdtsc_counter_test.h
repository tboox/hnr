/* ///////////////////////////////////////////////////////////////////////
 * File:		rdtsc_counter_test.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.06
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_RDTSC_COUNTER_TEST_H
#define EXTL_PLATFORM_WIN_RDTSC_COUNTER_TEST_H

#ifndef EXTL_PLATFORM_WIN_RDTSC_COUNTER_H
#	error This file must be included of rdtsc_counter.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct rdtsc_counter_test
{
	rdtsc_counter_test()
	{
		rdtsc_counter counter;
		counter.begin();
		Sleep(100);
		counter.end();
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("rdtsc_counter Test(10ms):\n"));
		EXTL_TEST_TRACE(_T("Count:   %u"), static_cast<e_uint32_t>(counter.count()));
	}
};

rdtsc_counter_test g_rdtsc_counter_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_RDTSC_COUNTER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

