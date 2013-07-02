/* ///////////////////////////////////////////////////////////////////////
 * File:		is_class_test.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09	
 *
 * Brief: is_class unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CLASS_H
#	error This file must be included of is_class.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

struct is_class_test_struct{};
struct is_class_test_class{};
union is_class_test_union{};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_class_test()
{
	EXTL_MUST_BE_CV_CLASS(is_class_test_class);
	EXTL_MUST_BE_CV_CLASS(is_class_test_struct);
	EXTL_MUST_NOT_BE_CV_CLASS(is_class_test_union);
	EXTL_MUST_NOT_BE_CV_CLASS(int);
	EXTL_MUST_NOT_BE_CV_CLASS(void);
	EXTL_MUST_NOT_BE_CV_CLASS(int *);
	EXTL_MUST_NOT_BE_CV_CLASS(int &);
	EXTL_MUST_NOT_BE_CV_CLASS(int [10]);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
