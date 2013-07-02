/* ///////////////////////////////////////////////////////////////////////
 * File:		tick_counter_test.h		
 *
 * Created:		08.02.17				
 * Updated:		08.11.09
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_TICK_COUNTER_TEST_H
#define EXTL_PLATFORM_WINDOWS_TICK_COUNTER_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(tick_counter_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct tick_counter_test
{
	tick_counter_test()
	{
		tick_counter counter;
		counter.start();
		::Sleep(100);
		counter.stop();
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("tick_counter Test(100ms):\n"));
		EXTL_TEST_TRACE(_T("Count:   %u"), static_cast<e_uint32_t>(counter.count()));
		EXTL_TEST_TRACE(_T("Seconds: %u"), static_cast<e_uint32_t>(counter.s()));
		EXTL_TEST_TRACE(_T("MS:      %u"), static_cast<e_uint32_t>(counter.ms()));
		EXTL_TEST_TRACE(_T("US:      %u"), static_cast<e_uint32_t>(counter.us()));
	}
};

tick_counter_test g_tick_counter_test;

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(tick_counter_test)
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_TICK_COUNTER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

