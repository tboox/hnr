/* ///////////////////////////////////////////////////////////////////////
 * File:		is_same_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: is_same unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_SAME_H
#	error This file must be included of is_same.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_same_test()
{
	EXTL_MUST_BE_CV_SAME(int, int);
	EXTL_MUST_BE_CV_SAME(int*, int*);
	EXTL_MUST_BE_CV_SAME(int**, int**);
	EXTL_MUST_BE_CV_SAME(int&, int&);
	EXTL_MUST_BE_CV_SAME(int[10], int[10]);
	EXTL_MUST_BE_CV_SAME(void, void);
	EXTL_MUST_BE_CV_SAME(void*, void*);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
