/* ///////////////////////////////////////////////////////////////////////
 * File:		is_union_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: is_union unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_UNION_H
#	error This file must be included of is_union.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
struct is_union_test_struct{};
union is_union_test_union{};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_union_test()
{
	union u{};
	struct s{};
#ifdef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT
	EXTL_MUST_BE_CV_UNION(is_union_test_union);
	EXTL_MUST_NOT_BE_CV_UNION(is_union_test_struct);
	EXTL_MUST_NOT_BE_CV_UNION(int);
	EXTL_MUST_NOT_BE_CV_UNION(void);
	EXTL_MUST_NOT_BE_CV_UNION(int *);
	EXTL_MUST_NOT_BE_CV_UNION(int &);
	EXTL_MUST_NOT_BE_CV_UNION(int [10]);
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
