/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_marray_test.h		
 *
 * Created:		08.08.05		
 * Updated:		08.08.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_FIXED_MARRAY_TEST_H
#define EXTL_CONTAINER_FIXED_MARRAY_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(fixed_marray_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int fixed_marray_test()
{
	typedef buffer_selector<int>::buffer_type	buffer_type;
	typedef fixed_marray<2, int, buffer_type>	array_type;

	int buf1[] = {	1, 2, 3, 4 , 
					5, 6, 7, 8, 
					9, 10, 11, 12
				};
	array_type ar1(buf1, 3, 4);

	EXTL_ASSERT(ar1.dim0() == 3);
	EXTL_ASSERT(ar1.dim1() == 4);
	EXTL_ASSERT(ar1.size() == 12);

	EXTL_ASSERT(ar1[1].dim0() == 4);
	EXTL_ASSERT(ar1[1].size() == 4);

	EXTL_ASSERT(ar1[1][1] == 6);

	EXTL_ASSERT(ar1.front() == 1);
	EXTL_ASSERT(ar1.back() == 12);
	EXTL_ASSERT(ar1[1].front() == 5);
	EXTL_ASSERT(ar1[1].back() == 8);

	array_type ar2(1, 3, 4); // 3 * 4 , initialized value: 1
	ar2.swap(ar1);

	EXTL_ASSERT(ar2.dim0() == 3);
	EXTL_ASSERT(ar2.dim1() == 4);
	EXTL_ASSERT(ar2.size() == 12);

	EXTL_ASSERT(ar2[1].dim0() == 4);
	EXTL_ASSERT(ar2[1].size() == 4);

	EXTL_ASSERT(ar2[1][1] == 6);
	EXTL_ASSERT(ar1[1][1] == 1);

	EXTL_ASSERT(ar2.front() == 1);
	EXTL_ASSERT(ar2.back() == 12);
	EXTL_ASSERT(ar2[1].front() == 5);
	EXTL_ASSERT(ar2[1].back() == 8);

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

int fixed_marray_test_ret = fixed_marray_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(fixed_marray_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_FIXED_MARRAY_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

