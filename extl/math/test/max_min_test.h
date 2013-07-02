/* ///////////////////////////////////////////////////////////////////////
 * File:		max_min_test.h		
 *
 * Created:		08.02.25			
 * Updated:		09.01.26
 *
 * Brief:		The max_min unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_MAX_MIN_TEST_H
#define EXTL_MATH_MAX_MIN_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(max_min_test)

struct max_min_test
{
	max_min_test()
	{
	#ifdef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT
		EXTL_ASSERT(xtl_max(1, 2.5) > 2.0);
		EXTL_ASSERT(xtl_max(1, 2, 3.5) > 3.0);
		EXTL_ASSERT(xtl_max(1, 2, 3, 4.5) > 4.0);

		EXTL_ASSERT((xtl_min(1.5, 2) > 1) && (xtl_min(1.5, 2) < 2));
		EXTL_ASSERT((xtl_min(1.5, 2, 3) > 1) && (xtl_min(1.5, 2, 3) < 2));
		EXTL_ASSERT((xtl_min(1.5, 2, 3, 4) > 1) && (xtl_min(1.5, 2, 3, 4) < 2));
	#endif
		EXTL_ASSERT(xtl_max(1, 2) == 2);
		EXTL_ASSERT(xtl_max(1, 2, 3) == 3);
		EXTL_ASSERT(xtl_max(1, 2, 3, 4) == 4);

		EXTL_ASSERT(xtl_min(1, 2) == 1);
		EXTL_ASSERT(xtl_min(1, 2, 3) == 1);
		EXTL_ASSERT(xtl_min(1, 2, 3, 4) == 1);
	}

};

max_min_test g_max_min_test;

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(max_min_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_MAX_MIN_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

