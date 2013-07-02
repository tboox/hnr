/* ///////////////////////////////////////////////////////////////////////
 * File:		pod_pool_test.h		
 *
 * Created:		08.04.21				
 * Updated:		08.04.21
 *
 * Brief: pod_pool class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_POD_POOL_TEST_H
#define EXTL_MEMORY_POD_POOL_TEST_H

#ifndef EXTL_MEMORY_POD_POOL_H
#	error This file must be included of pod_pool.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct pod_pool_test
{
	pod_pool_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("pod_pool Test:\n"));

	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		pod_pool<int> pool;
	#else
		pod_pool<int, typename_type_k allocator_selector<e_byte_t>::allocator_type > pool;
	#endif
		volatile int i = 0;
		clock_counter counter;


		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			int* p = pool.allocate();
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("pod_pool time:%d ms"), counter.count());


		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			void* p = malloc(sizeof(int));
			free(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms"), counter.count());

	}
};
pod_pool_test g_pod_pool_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_POD_POOL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

