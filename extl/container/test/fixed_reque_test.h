/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_reque_test.h		
 *
 * Created:		08.08.21			
 * Updated:		08.08.21
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_FIXED_REQUE_TEST_H
#define EXTL_CONTAINER_FIXED_REQUE_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(fixed_reque_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int fixed_reque_test()
{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef fixed_reque<int, 5>	reque_type;
#else
	typedef fixed_reque	<	int
						,	5
						,	buffer_selector<int>::buffer_type
						>		reque_type;
#endif

	reque_type q(10, 3);
	EXTL_ASSERT(q.size() == 3);
	EXTL_ASSERT(q.capacity() == 5);
	EXTL_ASSERT(q.front() == 10);
	EXTL_ASSERT(q.back() == 10);
	q.push_front(1);
	EXTL_ASSERT(q.front() == 1);
	q.push_back(2);
	EXTL_ASSERT(q.back() == 2);
	EXTL_ASSERT(q.is_full());
	q.pop_back();
	q.pop_front();
	EXTL_ASSERT(q.front() == 10);
	EXTL_ASSERT(q.back() == 10);
	EXTL_ASSERT(q.size() == 3);
	EXTL_ASSERT(q.capacity() == 5);
	q.pop_front();
	q.pop_front();
	q.pop_back();
	EXTL_ASSERT(q.is_empty());

	q.push_back(1);
	q.push_back(2);
	q.push_front(1);
	q.push_front(2);
	
//	for (reque_type::const_iterator p = q.begin(); p != q.end(); ++p)
//	{
//		printf("%d ", *p);
//	}
	return 0;
}
int fixed_reque_test_ret = fixed_reque_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(fixed_reque_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_FIXED_REQUE_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

