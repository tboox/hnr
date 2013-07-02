/* ///////////////////////////////////////////////////////////////////////
 * File:		is_abstract_test.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09	
 *
 * Brief: is_abstract unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_ABSTRACT_H
#	error This file must be included of is_abstract.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

class is_abstract_test_abstract{virtual ~is_abstract_test_abstract() = 0;};
union is_abstract_test_union{};
struct is_abstract_test_struct{};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_abstract_test()
{
	EXTL_MUST_BE_CV_ABSTRACT(is_abstract_test_abstract);
	EXTL_MUST_NOT_BE_CV_ABSTRACT(is_abstract_test_abstract *);
	EXTL_MUST_NOT_BE_CV_ABSTRACT(is_abstract_test_struct);
	EXTL_MUST_NOT_BE_CV_ABSTRACT(is_abstract_test_union);
	EXTL_MUST_NOT_BE_CV_ABSTRACT(int);
	EXTL_MUST_NOT_BE_CV_ABSTRACT(void);
	EXTL_MUST_NOT_BE_CV_ABSTRACT(int *);
	EXTL_MUST_NOT_BE_CV_ABSTRACT(int &);
	EXTL_MUST_NOT_BE_CV_ABSTRACT(int [10]);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
