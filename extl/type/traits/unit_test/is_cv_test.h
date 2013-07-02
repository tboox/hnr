/* ///////////////////////////////////////////////////////////////////////
 * File:		is_cv_test.h		
 *
 * Created:		08.02.02					
 * Updated:		08.07.09	
 *
 * Brief: is_cv unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CV_H
#	error This file must be included of is_cv.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_cv_test()
{
	EXTL_MUST_BE_CV(int const volatile);
	EXTL_MUST_BE_CV(int (*const volatile)());
	EXTL_MUST_BE_CV(int *const volatile);
	EXTL_MUST_BE_CV(int const volatile[10]);
	EXTL_MUST_NOT_BE_CV(int);
	EXTL_MUST_NOT_BE_CV(int&);
	EXTL_MUST_NOT_BE_CV(int const *);
	EXTL_MUST_NOT_BE_CV(int volatile*);
	EXTL_MUST_NOT_BE_CV(int const volatile*);
	EXTL_MUST_NOT_BE_CV(int const volatile&);
	EXTL_MUST_NOT_BE_CV(int *const);
	EXTL_MUST_NOT_BE_CV(int *volatile);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
