/* ///////////////////////////////////////////////////////////////////////
 * File:		objects_pool_test.h		
 *
 * Created:		08.04.14				
 * Updated:		08.04.28
 *
 * Brief: objects_pool class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_OBJECTS_POOL_TEST_H
#define EXTL_MEMORY_OBJECTS_POOL_TEST_H

#ifndef EXTL_MEMORY_OBJECTS_POOL_H
#	error This file must be included of objects_pool.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct objects_pool_test
{
	struct obj
	{
		obj(){}
		~obj(){}
	};
	e_size_t pool_rand(e_size_t& seed)
	{
		return (seed = (seed * 10807L) & 0x7fffffffL);
	}
	objects_pool_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("objects_pool Test:\n"));

	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		objects_pool<obj> pool;
	#else
		objects_pool<	obj
					,	initialiser_selector<obj>::initialiser_type
					> pool;
	#endif
		volatile int i = 0;
		clock_counter counter;
		e_size_t seed = 0, cur_seed = 100;

		/* ///////////////////////////////////////////////////////////////////////
		 * deallocate memory to pool at once: alloc_size:(0 - 64K), alloc_count: 100000
		 */
		EXTL_TEST_TRACE(_T("deallocate memory to pool at once: alloc_size:(0 - 64K), alloc_count: 1000"));
		seed = cur_seed;
		counter.begin();
		for(i=0; i < 1000; i++)
		{
			obj *p = pool.allocate(pool_rand(seed)%(64 * 1024));
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("objects_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		seed = cur_seed;
		counter.begin();
		for(i=0; i < 1000; i++)
		{
			obj *p = new obj[pool_rand(seed)%(64 * 1024)];
			delete[] p;
		}
		counter.end();
		EXTL_TEST_TRACE(_T("new time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * deallocate memory to pool at once: alloc_size:(0 - 1024K), alloc_count: 100000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("deallocate memory to pool at once: alloc_size:(0 - 1024K), alloc_count: 1000"));
		seed = cur_seed;
		counter.begin();
		for(i=0; i < 1000; i++)
		{
			obj *p = pool.allocate(pool_rand(seed)%(1024 * 1024));
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("objects_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		seed = cur_seed;
		counter.begin();
		for(i=0; i < 1000; i++)
		{
			obj *p = new obj[pool_rand(seed)%(1024 * 1024)];
			delete[] p;
		}
		counter.end();
		EXTL_TEST_TRACE(_T("new time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 8K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 4K), alloc_count: 1000"));
		obj* pa[200];
		seed = cur_seed;
		counter.begin();
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = pool.allocate(pool_rand(seed)%(4 * 1024));
			for(j = 0; j < 100; j++)
				pool.deallocate(pa[j]);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("objects_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		seed = cur_seed;
		counter.begin();
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = new obj[pool_rand(seed)%(4 * 1024)];
			for(j = 0; j < 100; j++)
				delete[] pa[j];
		}
		counter.end();
		EXTL_TEST_TRACE(_T("new time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 64K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 64K), alloc_count: 1000"));
		counter.begin();
		seed = cur_seed;
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = pool.allocate(pool_rand(seed)%(64 * 1024));
			for(j = 0; j < 100; j++)
				pool.deallocate(pa[j]);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("objects_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		seed = cur_seed;
		counter.begin();
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = new obj[pool_rand(seed)%(64 * 1024)];
			for(j = 0; j < 100; j++)
				delete[] pa[j];
		}
		counter.end();
		EXTL_TEST_TRACE(_T("new time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 1024K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 1024K), alloc_count: 1000"));
		seed = cur_seed;
		counter.begin();
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = pool.allocate(pool_rand(seed)%(1024 * 1024));
			for(j = 0; j < 100; j++)
				pool.deallocate(pa[j]);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("objects_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		seed = cur_seed;
		counter.begin();
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = new obj[pool_rand(seed)%(1024 * 1024)];
			for(j = 0; j < 100; j++)
				delete[] pa[j];
		}
		counter.end();
		EXTL_TEST_TRACE(_T("new time:%d ms\n"), counter.count());

		/* ///////////////////////////////////////////////////////////////////////
		 * reallocate memory: realloc_size:(0 - 64K), realloc_count: 50000
		 */
		//pool.destroy();
		//pool.create();
		obj* pr = pool.allocate(1); 
		EXTL_TEST_TRACE(_T("reallocate memory: realloc_size:(0 - 64K), realloc_count: 50000"));
		seed = cur_seed;
		counter.begin();
		for(i=0; i < 50000; i++)
			pr = pool.reallocate(pr, pool_rand(seed)%(64 * 1024));
		counter.end();
		pool.deallocate(pr);
		EXTL_TEST_TRACE(_T("objects_pool time:%d ms"), counter.count());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		seed = cur_seed;
		counter.begin();
		void* pm = malloc(1);
		for(i=0; i < 50000; i++)
		{
			pm = realloc(pm, pool_rand(seed)%(64 * 1024));
		}
		counter.end();
		free(pm);
		EXTL_TEST_TRACE(_T("realloc time:%d ms\n"), counter.count());
	}
};
objects_pool_test g_objects_pool_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_OBJECTS_POOL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

