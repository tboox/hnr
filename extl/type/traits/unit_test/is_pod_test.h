/* ///////////////////////////////////////////////////////////////////////
 * File:		is_pod.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.13
 *
 * Brief: is_pod unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_POD_H
#	error This file must be included of is_pod.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

struct is_pod_test_struct{};
struct is_pod_test_virtual_struct
{
	is_pod_test_virtual_struct(){};
	virtual ~is_pod_test_virtual_struct(){};
};
union is_pod_test_union{};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_pod_test()
{
	EXTL_MUST_BE_CV_POD(int);
	EXTL_MUST_BE_CV_POD(int[10]);
	EXTL_MUST_BE_CV_POD(int*);
	EXTL_MUST_BE_CV_POD(void);
	EXTL_MUST_BE_CV_POD(is_pod_test_virtual_struct *);
	EXTL_MUST_BE_CV_POD(is_pod_test_union);
	EXTL_MUST_BE_CV_POD(is_pod_test_union[10][10]);
	EXTL_MUST_BE_CV_POD(is_pod_test_struct);

	EXTL_MUST_NOT_BE_CV_POD(int&);
	EXTL_MUST_NOT_BE_CV_POD(is_pod_test_virtual_struct);
	EXTL_MUST_NOT_BE_CV_POD(is_pod_test_virtual_struct [10]);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
