/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_vvector_test.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.07
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Wvvuqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MATH_BASIC_VVECTOR_TEST_H
#define EXTL_MATH_BASIC_VVECTOR_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(basic_vvector_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int basic_vvector_test()
{
	typedef buffer_selector<int>::buffer_type		buffer_type;
	typedef basic_vvector<int, buffer_type >		vvector_type;

	int buf1[] = { 1, 2, 3, 4 , 5, 6, 7, 8,  9, 10, 11, 12 };
	vvector_type vv1(buf1, 12);

	EXTL_ASSERT(vv1.find_min() == 1);
	EXTL_ASSERT(vv1.find_max() == 12);
	EXTL_ASSERT(vv1.sum() == 78);

	EXTL_ASSERT(vv1.dim0() == 12);
	EXTL_ASSERT(vv1.size() == 12);

	EXTL_ASSERT(vv1[1] == 2);
	EXTL_ASSERT(vv1.front() == 1);
	EXTL_ASSERT(vv1.back() == 12);

	int buf2[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	vvector_type vv2(buf2, 12);

	vv2.swap(vv1);

	EXTL_ASSERT(vv2[1] == 2);
	EXTL_ASSERT(vv2.front() == 1);
	EXTL_ASSERT(vv2.back() == 12);

	vv2 += vv1;

	EXTL_ASSERT(vv2[1] == 3);
	EXTL_ASSERT(vv2.front() == 2);
	EXTL_ASSERT(vv2.back() == 13);

	vv2 -= 1;

	EXTL_ASSERT(vv2[1] == 2);
	EXTL_ASSERT(vv2.front() == 1);
	EXTL_ASSERT(vv2.back() == 12);

	vv2 = vv1 + 1;

	EXTL_ASSERT(vv2[1] == 2);
	EXTL_ASSERT(vv2.front() == 2);
	EXTL_ASSERT(vv2.back() == 2);

	vv2 = 1 - vv2;

	EXTL_ASSERT(vv2[1] == -1);
	EXTL_ASSERT(vv2.front() == -1);
	EXTL_ASSERT(vv2.back() == -1);

	vv2 = vv2 - vv2;

	EXTL_ASSERT(vv2[1] == 0);
	EXTL_ASSERT(vv2.front() == 0);
	EXTL_ASSERT(vv2.back() == 0);

	vv2++;

	EXTL_ASSERT(vv2[1] == 1);
	EXTL_ASSERT(vv2.front() == 1);
	EXTL_ASSERT(vv2.back() == 1);

	/*for (vvector_type::const_iterator p = vv2.begin(); p != vv2.end(); ++p)
	{
		printf("%d ", *p);
	}

	for (vvector_type::const_reverse_iterator rp = vv2.rbegin(); rp != vv2.rend(); ++rp)
	{
		printf("%d ", *rp);
	}*/

	return 0;
}

int basic_vvector_test_ret = basic_vvector_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_vvector_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_BASIC_VVECTOR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

