/* ///////////////////////////////////////////////////////////////////////
 * File:		max_min_test.h		
 *
 * Created:		08.05.13				
 * Updated:		08.05.13
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_MAX_MIN_TEST_H
#define EXTL_MPL_MATH_MAX_MIN_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void max_min_test()
{
	EXTL_STATIC_ASSERT((max<2, 3>::value == 3));
	EXTL_STATIC_ASSERT((max<2, 2>::value == 2));
	EXTL_STATIC_ASSERT((max_3<2, 2, 5>::value == 5));
	EXTL_STATIC_ASSERT((max_3<2, 2, 2>::value == 2));
	EXTL_STATIC_ASSERT((max_3<2, 0, 1>::value == 2));
	EXTL_STATIC_ASSERT((max_4<2, 0, 1, 5>::value == 5));

	EXTL_STATIC_ASSERT((min<2, 3>::value == 2));
	EXTL_STATIC_ASSERT((min<2, 2>::value == 2));
	EXTL_STATIC_ASSERT((min_3<2, 2, 5>::value == 2));
	EXTL_STATIC_ASSERT((min_3<2, 2, 2>::value == 2));
	EXTL_STATIC_ASSERT((min_3<2, 0, 1>::value == 0));
	EXTL_STATIC_ASSERT((min_4<2, 0, 1, 5>::value == 0));
}

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_MAX_MIN_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
