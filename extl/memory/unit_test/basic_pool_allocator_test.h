/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_pool_allocator_test.h		
 *
 * Created:		08.04.28			
 * Updated:		08.04.28	
 *
 * Brief: basic_pool_allocator class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_BASIC_POOL_ALLOCATOR_TEST_H
#define EXTL_MEMORY_BASIC_POOL_ALLOCATOR_TEST_H

#ifndef EXTL_MEMORY_BASIC_POOL_ALLOCATOR_H
#	error This file must be included of basic_pool_allocator.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct basic_pool_allocator_test
{
	basic_pool_allocator_test()
	{
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		typedef basic_pool_allocator<int> allocator_type;
	#else
		typedef basic_pool_allocator<	int
									,	synch_traits_selector::synch_traits_type
									,	default_basic_pool_allocator_tag
									> allocator_type;
	#endif
		allocator_type allocator;

		int *p = allocator.allocate(1);
		EXTL_ASSERT(p != NULL);

		*p = 10;
		EXTL_ASSERT(*p == 10);
	}
};

basic_pool_allocator_test g_basic_pool_allocator_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_BASIC_POOL_ALLOCATOR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

