/* ///////////////////////////////////////////////////////////////////////
 * File:		pods_pool_test.h		
 *
 * Created:		08.04.14				
 * Updated:		08.04.28
 *
 * Brief: pods_pool class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_PODS_POOL_TEST_H
#define EXTL_MEMORY_PODS_POOL_TEST_H

#ifndef EXTL_MEMORY_PODS_POOL_H
#	error This file must be included of pods_pool.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct pods_pool_test
{
	pods_pool_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("pods_pool Test:\n"));

		pods_pool<e_byte_t> pool;
		volatile int i = 0;
		clock_counter counter;

		/* ///////////////////////////////////////////////////////////////////////
		 * deallocate memory to pool at once: alloc_size:(0 - 64K), alloc_count: 100000
		 */
		EXTL_TEST_TRACE(_T("deallocate memory to pool at once: alloc_size:(0 - 64K), alloc_count: 1000000"));
		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			e_byte_t *p = pool.allocate(rand()%(64 * 1024));
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("pods_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			void *p = malloc(rand()%(64 * 1024));
			free(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * deallocate memory to pool at once: alloc_size:(0 - 1024K), alloc_count: 100000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("deallocate memory to pool at once: alloc_size:(0 - 1024K), alloc_count: 1000000"));
		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			e_byte_t *p = pool.allocate(rand()%(1024 * 1024));
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("pods_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			void *p = malloc(rand()%(1024 * 1024));
			free(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 8K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 1K), alloc_count: 20000"));
		e_byte_t* pa[200];
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 200; j++)
				pa[j] = pool.allocate(rand()%(1024));
			for(j = 0; j < 200; j++)
				pool.deallocate(pa[j]);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("pods_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 200; j++)
				pa[j] = static_cast<e_byte_t*>(malloc(rand()%(1024)));
			for(j = 0; j < 200; j++)
				free(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 64K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 64K), alloc_count: 20000"));
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 200; j++)
				pa[j] = pool.allocate(rand()%(64 * 1024));
			for(j = 0; j < 200; j++)
				pool.deallocate(pa[j]);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("pods_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 200; j++)
				pa[j] = static_cast<e_byte_t*>(malloc(rand()%(64 * 1024)));
			for(j = 0; j < 200; j++)
				free(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 1024K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 1024K), alloc_count: 20000"));
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 200; j++)
				pa[j] = pool.allocate(rand()%(1024 * 1024));
			for(j = 0; j < 200; j++)
				pool.deallocate(pa[j]);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("pods_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 200; j++)
				pa[j] = static_cast<e_byte_t*>(malloc(rand()%(1024 * 1024)));
			for(j = 0; j < 200; j++)
				free(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * reallocate memory: realloc_size:(0 - 64K), realloc_count: 50000
		 */
		//pool.destroy();
		//pool.create();
		e_byte_t* pr = pool.allocate(1); 
		EXTL_TEST_TRACE(_T("reallocate memory: realloc_size:(0 - 64K), realloc_count: 50000"));
		counter.begin();
		for(i=0; i < 50000; i++)
			pr = pool.reallocate(pr, rand()%(64 * 1024));
		counter.end();
		pool.deallocate(pr);
		EXTL_TEST_TRACE(_T("pods_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		
		counter.begin();
		void* pm = malloc(1);
		for(i=0; i < 50000; i++)
		{
			pm = realloc(pm, rand()%(64 * 1024));
		}
		counter.end();
		free(pm);
		EXTL_TEST_TRACE(_T("realloc time:%d ms\n"), counter.count());
	}
};
pods_pool_test g_pods_pool_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_PODS_POOL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

