/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_bound_test.h		
 *
 * Created:		08.02.12			
 * Updated:		08.07.13
 *
 * Brief: remove_bound unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_BOUND_H
#	error This file must be included of remove_bound.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void remove_bound_test()
{
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(int [10]));
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(char [10]));
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(float [10]));
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(int));
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(char));
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(float));

#if !(defined(EXTL_COMPILER_IS_BORLAND) && (__BORLANDC__ < 0x600)) 
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(int []));
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(char []));
	EXTL_MUST_BE_CV_ARITHMETIC(EXTL_REMOVE_BOUND(float []));
#endif

	EXTL_MUST_BE_CV_ARRAY(EXTL_REMOVE_BOUND(int [10][10]));
	EXTL_MUST_BE_CV_ARRAY(EXTL_REMOVE_BOUND(char [10][10]));
	EXTL_MUST_BE_CV_ARRAY(EXTL_REMOVE_BOUND(float [10][10]));
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
