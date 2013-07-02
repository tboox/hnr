/* ///////////////////////////////////////////////////////////////////////
 * File:		is_compound_test.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09	
 *
 * Brief: is_compound unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_COMPOUND_H
#	error This file must be included of is_compound.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_compound_test()
{
	EXTL_MUST_BE_CV_COMPOUND(int *);
#ifndef EXTL_COMPILER_IS_VECTORC
	EXTL_MUST_BE_CV_COMPOUND(int []);
#endif
	EXTL_MUST_BE_CV_COMPOUND(int [10]);
	EXTL_MUST_BE_CV_COMPOUND(int &);
	EXTL_MUST_NOT_BE_CV_COMPOUND(int);
	EXTL_MUST_NOT_BE_CV_COMPOUND(char);
	EXTL_MUST_NOT_BE_CV_COMPOUND(long);
	EXTL_MUST_NOT_BE_CV_COMPOUND(void);
	EXTL_MUST_NOT_BE_CV_COMPOUND(double);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
