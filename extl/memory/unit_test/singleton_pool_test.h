/* ///////////////////////////////////////////////////////////////////////
 * File:		singleton_pool_test.h		
 *
 * Created:		08.04.15				
 * Updated:		08.04.15	
 *
 * Brief: singleton_pool class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_SINGLETON_POOL_TEST_H
#define EXTL_MEMORY_SINGLETON_POOL_TEST_H

#ifndef EXTL_MEMORY_SINGLETON_POOL_H
#	error This file must be included of singleton_pool.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct singleton_pool_test
{
	struct singleton_pool_test_tag{};
	singleton_pool_test()
	{
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		typedef singleton_pool<singleton_pool_test_tag, object_pool<int> > pool;
	#else
		typedef singleton_pool	<	singleton_pool_test_tag
								,	object_pool	<	int 
												,	allocator_selector<e_byte_t>::allocator_type 
												>
								,	synch_traits_selector::synch_traits_type
								>			pool;
	#endif
		int* p = pool::allocate(1);
		*p = 10;
		EXTL_ASSERT(*p == 10);
		pool::deallocate(p);
		
	}
};
singleton_pool_test g_singleton_pool_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_SINGLETON_POOL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

