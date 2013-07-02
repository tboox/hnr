/* ///////////////////////////////////////////////////////////////////////
 * File:		is_enum_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.09	
 *
 * Brief: is_enum unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_ENUM_H
#	error This file must be included of is_enum.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
enum is_enum_test_enum{};
struct is_enum_test_struct{};
class is_enum_test_class{};
union is_enum_test_union{};

EXTL_INLINE void is_enum_test()
{
	EXTL_MUST_BE_CV_ENUM(is_enum_test_enum);
	EXTL_MUST_NOT_BE_CV_ENUM(is_enum_test_struct);
	EXTL_MUST_NOT_BE_CV_ENUM(is_enum_test_class);
	EXTL_MUST_NOT_BE_CV_ENUM(is_enum_test_union);
	EXTL_MUST_NOT_BE_CV_ENUM(int);
	EXTL_MUST_NOT_BE_CV_ENUM(double);
	EXTL_MUST_NOT_BE_CV_ENUM(double*);
	EXTL_MUST_NOT_BE_CV_ENUM(void*);
	EXTL_MUST_NOT_BE_CV_ENUM(void);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
