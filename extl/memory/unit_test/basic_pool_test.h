/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_pool_test.h		
 *
 * Created:		08.04.14				
 * Updated:		08.04.28
 *
 * Brief: basic_pool class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_BASIC_POOL_TEST_H
#define EXTL_MEMORY_BASIC_POOL_TEST_H

#ifndef EXTL_MEMORY_BASIC_POOL_H
#	error This file must be included of basic_pool.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct basic_pool_test
{
	e_size_t pool_rand(e_size_t& seed)
	{
		return (seed = (seed * 10807L) & 0x7fffffffL);
	}

	basic_pool_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("basic_pool Test:\n"));

		default_basic_pool pool;
		volatile int i = 0;
		e_size_t seed = 0, cur_seed = 100;
		clock_counter counter;

		linear_rand<0, 4 * 1024 > r1(100);
		linear_rand<0, 64 * 1024 > r2(100);
		linear_rand<0, 1024 * 1024 > r3(100);

		/* ///////////////////////////////////////////////////////////////////////
		 * deallocate memory to pool at once: alloc_size:(0 - 4K), alloc_count: 100000
		 */
		EXTL_TEST_TRACE(_T("deallocate memory to pool at once: alloc_size:(0 - 4K), alloc_count: 1000000"));
		counter.begin();
		for(i=0; i < 1000000; i++)
		{	
			void *p = pool.allocate(r1.generate());
			pool.deallocate(p);
		}
		counter.end();

		EXTL_TEST_TRACE(_T("basic_pool time:%d ms"), counter.ms());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		r1.reset();
		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			void *p = malloc(r1.generate());
			free(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.ms());

		/* ///////////////////////////////////////////////////////////////////////
		 * deallocate memory to pool at once: alloc_size:(0 - 64K), alloc_count: 100000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("deallocate memory to pool at once: alloc_size:(0 - 64K), alloc_count: 1000000"));
		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			void *p = pool.allocate(r2.generate());
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("basic_pool time:%d ms"), counter.ms());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		r2.reset();
		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			void *p = malloc(r2.generate());
			free(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.ms());

		/* ///////////////////////////////////////////////////////////////////////
		 * deallocate memory to pool at once: alloc_size:(0 - 1024K), alloc_count: 100000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("deallocate memory to pool at once: alloc_size:(0 - 1024K), alloc_count: 10000"));
		counter.begin();
		for(i=0; i < 10000; i++)
		{
			void *p = pool.allocate(r3.generate());
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("basic_pool time:%d ms"), counter.ms());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		r3.reset();
		counter.begin();
		for(i=0; i < 10000; i++)
		{
			void *p = malloc(r3.generate());
			free(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.ms());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 4K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 4K), alloc_count: 100000"));
		e_byte_t* pa[1000];
		r1.reset();
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 1000; j++)
				pa[j] = static_cast<e_byte_t*>(pool.allocate(r1.generate()));
			for(j = 0; j < 1000; j++)
				pool.deallocate(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("basic_pool time:%d ms"), counter.ms());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		r1.reset();
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 1000; j++)
				pa[j] = static_cast<e_byte_t*>(malloc(r1.generate()));
			for(j = 0; j < 1000; j++)
				free(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.ms());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 64K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 64K), alloc_count: 10000"));
		r2.reset();
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = static_cast<e_byte_t*>(pool.allocate(r2.generate()));
			for(j = 0; j < 100; j++)
				pool.deallocate(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("basic_pool time:%d ms"), counter.ms());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		r2.reset();
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = static_cast<e_byte_t*>(malloc(r2.generate()));
			for(j = 0; j < 100; j++)
				free(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.ms());

		/* ///////////////////////////////////////////////////////////////////////
		 * delay to deallocate memory to pool: alloc_size:(0 - 1024K), alloc_count: 20000
		 */
		//pool.destroy();
		//pool.create();
		EXTL_TEST_TRACE(_T("delay to deallocate memory to pool: alloc_size:(0 - 1024K), alloc_count: 10000"));
		r3.reset();
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = static_cast<e_byte_t*>(pool.allocate(r3.generate()));
			for(j = 0; j < 100; j++)
				pool.deallocate(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("basic_pool time:%d ms"), counter.ms());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		r3.reset();
		counter.begin();
		for(i=0; i < 100; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
				pa[j] = static_cast<e_byte_t*>(malloc(r3.generate()));
			for(j = 0; j < 100; j++)
				free(static_cast<e_byte_t*>(pa[j]));
		}
		counter.end();
		EXTL_TEST_TRACE(_T("malloc time:%d ms\n"), counter.ms());

		/* ///////////////////////////////////////////////////////////////////////
		 * reallocate memory: realloc_size:(0 - 64K), realloc_count: 50000
		 */
		//pool.destroy();
		//pool.create();
		void* pr = pool.allocate(1); 
		EXTL_TEST_TRACE(_T("reallocate memory: realloc_size:(0 - 64K), realloc_count: 50000"));
		r2.reset();
		counter.begin();
		for(i=0; i < 50000; i++)
			pr = pool.reallocate(pr, r2.generate());
		counter.end();
		pool.deallocate(pr);
		EXTL_TEST_TRACE(_T("basic_pool time:%d ms"), counter.ms());
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_system:%u"),pool.get_snapshot().cur_alloc_size_from_system);
		EXTL_TEST_TRACE(_T("cur_alloc_size_from_pool:%u"),pool.get_snapshot().cur_alloc_size_from_pool);

		r2.reset();
		counter.begin();
		pr = malloc(1);
		for(i=0; i < 50000; i++)
		{
			pr = realloc(pr, r2.generate());
		}
		counter.end();
		free(pr);
		EXTL_TEST_TRACE(_T("realloc time:%d ms\n"), counter.ms());

		/* ///////////////////////////////////////////////////////////////////////
		 * memory boundary check
		 */
		r1.reset();
		for(i=0; i < 1000; i++)
		{	
			e_size_t n = r1.generate();
			void *p = pool.allocate(n);
			mem_fill_0(p, n);
			pool.deallocate(p);
		}

		r2.reset();
		for(i=0; i < 1000; i++)
		{	
			e_size_t n = r2.generate();
			void *p = pool.allocate(n);
			mem_fill_0(p, n);
			pool.deallocate(p);
		}

		r3.reset();
		for(i=0; i < 1000; i++)
		{	
			e_size_t n = r3.generate();
			void *p = pool.allocate(n);
			mem_fill_0(p, n);
			pool.deallocate(p);
		}

		r1.reset();
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
			{
				e_size_t n = r1.generate();
				pa[j] = static_cast<e_byte_t*>(pool.allocate(n));
				mem_fill_0(static_cast<void*>(pa[j]), n);
			}
			for(j = 0; j < 100; j++)
				pool.deallocate(static_cast<e_byte_t*>(pa[j]));
		}

		r2.reset();
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
			{
				e_size_t n = r2.generate();
				pa[j] = static_cast<e_byte_t*>(pool.allocate(n));
				mem_fill_0(static_cast<void*>(pa[j]), n);
			}
			for(j = 0; j < 100; j++)
				pool.deallocate(static_cast<e_byte_t*>(pa[j]));
		}

		r3.reset();
		for(i=0; i < 10; i++)
		{
			volatile e_size_t j;
			for(j = 0; j < 100; j++)
			{
				e_size_t n = r3.generate();
				pa[j] = static_cast<e_byte_t*>(pool.allocate(n));
				mem_fill_0(static_cast<void*>(pa[j]), n);
			}
			for(j = 0; j < 100; j++)
				pool.deallocate(static_cast<e_byte_t*>(pa[j]));
		}
	}
};
basic_pool_test g_basic_pool_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_BASIC_POOL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

