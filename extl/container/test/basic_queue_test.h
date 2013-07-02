/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_queue_test.h		
 *
 * Created:		08.08.21			
 * Updated:		08.08.21
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_BASIC_QUEUE_TEST_H
#define EXTL_CONTAINER_BASIC_QUEUE_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(basic_queue_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int basic_queue_test()
{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_queue<int>			queue_type;
#else
	typedef fixed_reque	<	int
						,	5
						,	buffer_selector<int>::buffer_type
						>				reque_type;
	typedef basic_queue	<	reque_type
						,	basic_list	<	int
										,	allocator_selector<int>::allocator_type 
										,	memory_traits_selector<int>::memory_traits_type
										,	initialiser_selector<int>::initialiser_type
										>
						>				queue_type;
#endif

	queue_type q;
	EXTL_ASSERT(q.size() == 0);
	q.push(10);
	EXTL_ASSERT(q.front() == 10);
	EXTL_ASSERT(q.back() == 10);
	q.push(2);
	EXTL_ASSERT(q.front() == 10);
	EXTL_ASSERT(q.back() == 2);
	q.pop();
	EXTL_ASSERT(q.front() == 2);
	EXTL_ASSERT(q.back() == 2);
	EXTL_ASSERT(q.size() == 1);
	
	return 0;
}

int basic_queue_test_ret = basic_queue_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_queue_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_BASIC_QUEUE_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

