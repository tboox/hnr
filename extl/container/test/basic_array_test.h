/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_array_test.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.07
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_BASIC_ARRAY_TEST_H
#define EXTL_CONTAINER_BASIC_ARRAY_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(basic_array_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int basic_array_test()
{
	typedef buffer_selector<int>::buffer_type	buffer_type;
	typedef basic_array<int, buffer_type>		array_type;

	int buf1[] = { 1, 2, 3, 4 , 5, 6, 7, 8,  9, 10, 11, 12 };
	array_type ar1(buf1, 12);

	EXTL_ASSERT(ar1.dim0() == 12);
	EXTL_ASSERT(ar1.size() == 12);

	EXTL_ASSERT(ar1[1] == 2);
	EXTL_ASSERT(ar1.front() == 1);
	EXTL_ASSERT(ar1.back() == 12);

	array_type ar2(1, 12);

	ar2.swap(ar1);

	EXTL_ASSERT(ar2[1] == 2);
	EXTL_ASSERT(ar2.front() == 1);
	EXTL_ASSERT(ar2.back() == 12);

	/*for (array_type::const_iterator p = ar2.begin(); p != ar2.end(); ++p)
	{
		printf("%d ", *p);
	}

	for (array_type::const_reverse_iterator rp = ar2.rbegin(); rp != ar2.rend(); ++rp)
	{
		printf("%d ", *rp);
	}*/

	return 0;
}
int basic_array_test_ret = basic_array_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_array_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_BASIC_ARRAY_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

