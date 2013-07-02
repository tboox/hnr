/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_pool_test.h		
 *
 * Created:		08.04.15				
 * Updated:		08.05.01	
 *
 * Brief: fixed_pool class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_FIXED_POOL_TEST_H
#define EXTL_MEMORY_FIXED_POOL_TEST_H

#ifndef EXTL_MEMORY_FIXED_POOL_H
#	error This file must be included of fixed_pool.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct fixed_pool_test
{
	fixed_pool_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("fixed_pool Test:\n"));

	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		fixed_pool<sizeof(int)> pool;
	#else
		fixed_pool<sizeof(int), allocator_selector<e_byte_t>::allocator_type > pool;
	#endif
		volatile int i = 0, j = 0;
		clock_counter counter;

		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			void* p = pool.allocate();
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("fixed_pool time:%d ms"), counter.count());

		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			void* p = malloc(sizeof(int));
			free(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms"), counter.count());

		int* pa[3000];
		counter.begin();
		for(i=0; i < 1000; i++)
		{
			for(j = 0; j < 3000; j++)
				pa[j] = static_cast<int*>(pool.allocate());
			for(j = 0; j < 3000; j++)
				pool.deallocate(pa[j]);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("fixed_pool time:%d ms"), counter.count());

		counter.begin();
		for(i=0; i < 1000; i++)
		{
			for(j = 0; j < 3000; j++)
				pa[j] = static_cast<int*>(malloc(sizeof(int)));
			for(j = 0; j < 3000; j++)
				free(pa[j]);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms"), counter.count());
	}
};
fixed_pool_test g_fixed_pool_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_FIXED_POOL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

