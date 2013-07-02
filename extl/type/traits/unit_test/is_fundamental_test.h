/* ///////////////////////////////////////////////////////////////////////
 * File:		is_fundamental_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.09	
 *
 * Brief: is_fundamental unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_FUNDAMENTAL_H
#	error This file must be included of is_fundamental.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_fundamental_test()
{
	EXTL_MUST_BE_CV_FUNDAMENTAL(int);
	EXTL_MUST_BE_CV_FUNDAMENTAL(void);
	EXTL_MUST_BE_CV_FUNDAMENTAL(char);
	EXTL_MUST_BE_CV_FUNDAMENTAL(long);
	EXTL_MUST_NOT_BE_CV_FUNDAMENTAL(int *);
	EXTL_MUST_NOT_BE_CV_FUNDAMENTAL(int &);
	EXTL_MUST_NOT_BE_CV_FUNDAMENTAL(int [10]);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
