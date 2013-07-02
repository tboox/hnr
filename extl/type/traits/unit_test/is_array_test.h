/* ///////////////////////////////////////////////////////////////////////
 * File:		is_array_test.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09	
 *
 * Brief: is_array unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_ARRAY_H
#	error This file must be included of is_array.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_array_test()
{
#if !defined(EXTL_COMPILER_IS_BORLAND) && \
		!defined(EXTL_COMPILER_IS_VECTORC)
	EXTL_MUST_BE_CV_ARRAY(int []);
#endif
	EXTL_MUST_BE_CV_ARRAY(int [10]);

	EXTL_MUST_NOT_BE_CV_ARRAY(void);
	EXTL_MUST_NOT_BE_CV_ARRAY(int *);
	EXTL_MUST_NOT_BE_CV_ARRAY(int &);

	EXTL_MUST_NOT_BE_ARRAY(int (*)());

	typedef int (is_func_test_0)();
	EXTL_MUST_NOT_BE_ARRAY(is_func_test_0);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
