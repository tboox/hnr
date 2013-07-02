/* ///////////////////////////////////////////////////////////////////////
 * File:		is_convertible_test.h		
 *
 * Created:		08.02.02					
 * Updated:		08.07.09	
 *
 * Brief: is_convertible unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_H
#	error This file must be included of is_convertible.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_convertible_test()
{
	EXTL_MUST_BE_CV_CONVERTIBLE(char, int);
	EXTL_MUST_BE_CV_CONVERTIBLE(int, int);
	EXTL_MUST_BE_CV_CONVERTIBLE(int, int&);
	EXTL_MUST_BE_CV_CONVERTIBLE(void, void);
	EXTL_MUST_BE_CV_CONVERTIBLE(char*, void*);
	EXTL_MUST_BE_CV_CONVERTIBLE(int, float);
	EXTL_MUST_BE_CV_CONVERTIBLE(float, double);

#if !defined(EXTL_COMPILER_IS_BORLAND)
	EXTL_MUST_NOT_BE_CV_CONVERTIBLE(char, void);
	EXTL_MUST_NOT_BE_CV_CONVERTIBLE(int, int[10]);
	EXTL_MUST_NOT_BE_CV_CONVERTIBLE(int, int*);
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
