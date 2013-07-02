/* ///////////////////////////////////////////////////////////////////////
 * File:		is_float_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.09	
 *
 * Brief: is_float unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_FLOAT_H
#	error This file must be included of is_float.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_float_test()
{
	EXTL_MUST_BE_CV_FLOAT(float);
	EXTL_MUST_NOT_BE_CV_FLOAT(int);
	EXTL_MUST_NOT_BE_CV_FLOAT(float *);
	EXTL_MUST_NOT_BE_CV_FLOAT(float &);
	EXTL_MUST_NOT_BE_CV_FLOAT(float [10]);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
