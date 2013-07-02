/* ///////////////////////////////////////////////////////////////////////
 * File:		is_polymorphic_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.13
 *
 * Brief: is_polymorphic unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_POLYMORPHIC_H
#	error This file must be included of is_polymorphic.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

struct is_polymorphic_test_abstract{virtual ~is_polymorphic_test_abstract() = 0;};
union is_polymorphic_test_union{};
struct is_polymorphic_test_struct{};
struct is_polymorphic_test_virtual{virtual ~is_polymorphic_test_virtual();};
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_polymorphic_test()
{
	EXTL_MUST_BE_CV_POLYMORPHIC(is_polymorphic_test_abstract);
	EXTL_MUST_BE_CV_POLYMORPHIC(is_polymorphic_test_virtual);

	EXTL_MUST_NOT_BE_CV_POLYMORPHIC(is_polymorphic_test_struct);
	EXTL_MUST_NOT_BE_CV_POLYMORPHIC(is_polymorphic_test_abstract *);
	EXTL_MUST_NOT_BE_CV_POLYMORPHIC(is_polymorphic_test_union);
	EXTL_MUST_NOT_BE_CV_POLYMORPHIC(int);
	EXTL_MUST_NOT_BE_CV_POLYMORPHIC(void);
	EXTL_MUST_NOT_BE_CV_POLYMORPHIC(int *);
	EXTL_MUST_NOT_BE_CV_POLYMORPHIC(int &);
	EXTL_MUST_NOT_BE_CV_POLYMORPHIC(int [10]);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
