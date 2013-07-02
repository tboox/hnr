/* ///////////////////////////////////////////////////////////////////////
 * File:		is_scalar_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: is_scalar unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_SCALAR_H
#	error This file must be included of is_scalar.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
struct is_scalar_test_struct{};
struct is_scalar_test_class{};
union is_scalar_test_union{};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_scalar_test()
{
	EXTL_MUST_BE_CV_SCALAR(int);
	EXTL_MUST_BE_CV_SCALAR(int*);
	EXTL_MUST_BE_CV_SCALAR(void*);
	EXTL_MUST_BE_CV_SCALAR(is_scalar_test_struct*);
	EXTL_MUST_BE_CV_SCALAR(float);
	EXTL_MUST_NOT_BE_CV_SCALAR(void);
	EXTL_MUST_NOT_BE_CV_SCALAR(int &);
	EXTL_MUST_NOT_BE_CV_SCALAR(is_scalar_test_struct);
	EXTL_MUST_NOT_BE_CV_SCALAR(is_scalar_test_union);
	EXTL_MUST_NOT_BE_CV_SCALAR(is_scalar_test_class);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
