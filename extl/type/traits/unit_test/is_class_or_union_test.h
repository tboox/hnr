/* ///////////////////////////////////////////////////////////////////////
 * File:		is_class_or_union_test.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09	
 *
 * Brief: is_class_or_union unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_H
#	error This file must be included of is_class_or_union.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

struct is_class_or_union_test_struct{};
struct is_class_or_union_test_class{};
union is_class_or_union_test_union{};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_class_or_union_test()
{
	EXTL_MUST_BE_CV_CLASS_OR_UNION(is_class_or_union_test_class);
	EXTL_MUST_BE_CV_CLASS_OR_UNION(is_class_or_union_test_struct);
	EXTL_MUST_BE_CV_CLASS_OR_UNION(is_class_or_union_test_union);

	EXTL_MUST_NOT_BE_CV_CLASS_OR_UNION(int);
	EXTL_MUST_NOT_BE_CV_CLASS_OR_UNION(void);
	EXTL_MUST_NOT_BE_CV_CLASS_OR_UNION(int *);
	EXTL_MUST_NOT_BE_CV_CLASS_OR_UNION(int &);
	EXTL_MUST_NOT_BE_CV_CLASS_OR_UNION(int [10]);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
