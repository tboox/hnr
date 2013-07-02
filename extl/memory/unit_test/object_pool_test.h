/* ///////////////////////////////////////////////////////////////////////
 * File:		object_pool_test.h		
 *
 * Created:		08.04.15				
 * Updated:		08.04.15	
 *
 * Brief: object_pool class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_OBJECT_POOL_TEST_H
#define EXTL_MEMORY_OBJECT_POOL_TEST_H

#ifndef EXTL_MEMORY_OBJECT_POOL_H
#	error This file must be included of object_pool.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct object_pool_test
{
	struct obj
	{
		obj(){}
		~obj(){}
	};
	object_pool_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("object_pool Test:\n"));

	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		object_pool<obj> pool;
	#else
		object_pool	<	obj
					,	initialiser_selector<obj>::initialiser_type
					,	EXTL_FIXED_POOL_DEFAULT_CHUNK_SIZE
					,	allocator_selector<e_byte_t>::allocator_type
					>							pool;
	#endif
		volatile int i = 0;
		clock_counter counter;

		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			obj* p = pool.allocate();
			pool.deallocate(p);
		}
		counter.end();
		EXTL_TEST_TRACE(_T("object_pool time:%d ms"), counter.count());

		counter.begin();
		for(i=0; i < 1000000; i++)
		{
			obj* p = new obj;
			delete p;
		}
		counter.end();
		EXTL_TEST_TRACE(_T("new time:%d ms"), counter.count());

	}
};
object_pool_test g_object_pool_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_OBJECT_POOL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

