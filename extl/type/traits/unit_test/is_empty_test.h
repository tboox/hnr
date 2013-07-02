/* ///////////////////////////////////////////////////////////////////////
 * File:		is_empty_test.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09	
 *
 * Brief: is_empty unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_EMPTY_H
#	error This file must be included of is_empty.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
struct is_empty_test_virtual{virtual ~is_empty_test_virtual();}; /* non-empty */
union is_empty_test_union{};
struct is_empty_test_struct{};
struct is_empty_test_struct_no_empty{e_byte_t padding[10];};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_empty_test()
{
	EXTL_MUST_BE_CV_EMPTY(is_empty_test_struct);
	EXTL_MUST_BE_CV_EMPTY(is_empty_test_union);

	EXTL_MUST_NOT_BE_CV_EMPTY(is_empty_test_struct *);
	EXTL_MUST_NOT_BE_CV_EMPTY(is_empty_test_struct_no_empty);
	EXTL_MUST_NOT_BE_CV_EMPTY(is_empty_test_virtual);
	EXTL_MUST_NOT_BE_CV_EMPTY(int);
	EXTL_MUST_NOT_BE_CV_EMPTY(void);
	EXTL_MUST_NOT_BE_CV_EMPTY(int *);
	EXTL_MUST_NOT_BE_CV_EMPTY(int &);
	EXTL_MUST_NOT_BE_CV_EMPTY(int [10]);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
