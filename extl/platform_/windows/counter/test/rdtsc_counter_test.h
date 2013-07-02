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
#ifndef EXTL_PLATFORM_WINDOWS_RDTSC_COUNTER_TEST_H
#define EXTL_PLATFORM_WINDOWS_RDTSC_COUNTER_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(rdtsc_counter_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct rdtsc_counter_test
{
	rdtsc_counter_test()
	{
		rdtsc_counter counter;
		counter.start();
		Sleep(100);
		counter.stop();
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("rdtsc_counter Test(10ms):\n"));
		EXTL_TEST_TRACE(_T("Count:   %u"), static_cast<e_uint32_t>(counter.count()));
	}
};

rdtsc_counter_test g_rdtsc_counter_test;

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(rdtsc_counter_test)
EXTL_WINDOWS_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_RDTSC_COUNTER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

