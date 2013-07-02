/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_varray_test.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.07
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MATH_BASIC_VARRAY_TEST_H
#define EXTL_MATH_BASIC_VARRAY_TEST_H

#ifndef EXTL_MATH_BASIC_VARRAY_H
#	error This file must be included of basic_varray.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(basic_varray_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct basic_varray_test
{
	basic_varray_test()
	{
		typedef buffer_selector<int>::buffer_type	buffer_type;
		typedef basic_varray<int, buffer_type >		array_type;

		int buf1[] = { 1, 2, 3, 4 , 5, 6, 7, 8,  9, 10, 11, 12 };
		array_type ar1(buf1, 12);

		EXTL_ASSERT(ar1.min_() == 1);
		EXTL_ASSERT(ar1.max_() == 12);
		EXTL_ASSERT(ar1.sum_() == 78);

		EXTL_ASSERT(ar1.dim0() == 12);
		EXTL_ASSERT(ar1.size() == 12);

		EXTL_ASSERT(ar1[1] == 2);
		EXTL_ASSERT(ar1.front() == 1);
		EXTL_ASSERT(ar1.back() == 12);

		int buf2[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		array_type ar2(buf2, 12);

		ar2.swap(ar1);

		EXTL_ASSERT(ar2[1] == 2);
		EXTL_ASSERT(ar2.front() == 1);
		EXTL_ASSERT(ar2.back() == 12);

		ar2 += ar1;

		EXTL_ASSERT(ar2[1] == 3);
		EXTL_ASSERT(ar2.front() == 2);
		EXTL_ASSERT(ar2.back() == 13);

		ar2 -= 1;

		EXTL_ASSERT(ar2[1] == 2);
		EXTL_ASSERT(ar2.front() == 1);
		EXTL_ASSERT(ar2.back() == 12);

		ar2 = ar1 + 1;

		EXTL_ASSERT(ar2[1] == 2);
		EXTL_ASSERT(ar2.front() == 2);
		EXTL_ASSERT(ar2.back() == 2);

		ar2 = 1 - ar2;

		EXTL_ASSERT(ar2[1] == -1);
		EXTL_ASSERT(ar2.front() == -1);
		EXTL_ASSERT(ar2.back() == -1);

		ar2 = ar2 - ar2;

		EXTL_ASSERT(ar2[1] == 0);
		EXTL_ASSERT(ar2.front() == 0);
		EXTL_ASSERT(ar2.back() == 0);

		ar2++;

		EXTL_ASSERT(ar2[1] == 1);
		EXTL_ASSERT(ar2.front() == 1);
		EXTL_ASSERT(ar2.back() == 1);

		EXTL_ASSERT((-ar2)[0] == -1);
		EXTL_ASSERT((!ar2)[0] == 0);

		ar2 = 2 << ar2 ^ 3 & ar2 % 100 | 5 >> 2;

		/*for (array_type::const_iterator p = ar2.begin(); p != ar2.end(); ++p)
		{
			printf("%d ", *p);
		}

		for (array_type::const_reverse_iterator rp = ar2.rbegin(); rp != ar2.rend(); ++rp)
		{
			printf("%d ", *rp);
		}*/

	}
};

basic_varray_test g_basic_varray_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_varray_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_BASIC_VARRAY_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

