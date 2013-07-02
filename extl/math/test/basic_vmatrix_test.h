/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_vmatrix_test.h		
 *
 * Created:		08.08.10		
 * Updated:		08.08.10
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MATH_BASIC_VMATRIX_TEST_H
#define EXTL_MATH_BASIC_VMATRIX_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(basic_vmatrix_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int basic_vmatrix_test()
{
	typedef buffer_selector<int>::buffer_type	buffer_type;
	typedef basic_vmatrix<int, buffer_type>		vmatrix_type;

	int buf1[] = {	1, 2, 3, 4 , 
					5, 6, 7, 8,  
					9, 10, 11, 12 };
	vmatrix_type ma1(buf1, 3, 4);

	EXTL_ASSERT(ma1.find_min() == 1);
	EXTL_ASSERT(ma1.find_max() == 12);
	EXTL_ASSERT(ma1.sum() == 78);


	EXTL_ASSERT(ma1.dim0() == 3);
	EXTL_ASSERT(ma1.dim1() == 4);
	EXTL_ASSERT(ma1[0].dim0() == 4);
	EXTL_ASSERT(ma1.size() == 12);

	EXTL_ASSERT(ma1[1][0] == 5);
	EXTL_ASSERT(ma1.front() == 1);
	EXTL_ASSERT(ma1.back() == 12);

	vmatrix_type ma2(1, 3, 4);

	ma2.swap(ma1);

	EXTL_ASSERT(ma2.at(1, 0) == 5);
	EXTL_ASSERT(ma2.front() == 1);
	EXTL_ASSERT(ma2.back() == 12);

	ma2 += ma1;

	EXTL_ASSERT(ma2[1][0] == 6);
	EXTL_ASSERT(ma2.front() == 2);
	EXTL_ASSERT(ma2.back() == 13);

	ma2 -= 1;

	EXTL_ASSERT(ma2[1][0] == 5);
	EXTL_ASSERT(ma2.front() == 1);
	EXTL_ASSERT(ma2.back() == 12);

	ma2 = ma1 + 1;

	EXTL_ASSERT(ma2[1][0] == 2);
	EXTL_ASSERT(ma2.front() == 2);
	EXTL_ASSERT(ma2.back() == 2);

	ma2 = 1 - ma2;

	EXTL_ASSERT(ma2[1][0] == -1);
	EXTL_ASSERT(ma2.front() == -1);
	EXTL_ASSERT(ma2.back() == -1);

	ma2 = ma2 - ma2;

	EXTL_ASSERT(ma2[1][0] == 0);
	EXTL_ASSERT(ma2.front() == 0);
	EXTL_ASSERT(ma2.back() == 0);

	ma2++;

	EXTL_ASSERT(ma2[1][0] == 1);
	EXTL_ASSERT(ma2.front() == 1);
	EXTL_ASSERT(ma2.back() == 1);

	/*for (vmatrix_type::const_iterator p = ma2.begin(); p != ma2.end(); ++p)
	{
		printf("%d ", *p);
	}

	for (vmatrix_type::const_reverse_iterator rp = ma2.rbegin(); rp != ma2.rend(); ++rp)
	{
		printf("%d ", *rp);
	}*/

	/*int p1[] = { 1, 2, 3};
	int p2[] = { 4, 5, 5};
	basic_vvector<int> v1(p1, 3, false);
	basic_vvector<int> v2(p2, 3);
	basic_vmatrix<int> vm;

	vm = v1 * v2;
	printf("%d\n", vm[0][0]);
	printf("%d\n", vm[0][1]);
	printf("%d\n", vm[1][0]);
	printf("%d\n", vm[1][1]);
	printf("%d\n", vm[2][0]);
	printf("%d\n", vm[2][1]);*/
	return 0;
}
int basic_vmatrix_test_ret = basic_vmatrix_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_vmatrix_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_BASIC_VMATRIX_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

