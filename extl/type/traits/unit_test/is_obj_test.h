/* ///////////////////////////////////////////////////////////////////////
 * File:		is_obj_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.13
 *
 * Brief: is_obj unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_OBJ_H
#	error This file must be included of is_obj.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_obj_test()
{
	EXTL_MUST_BE_CV_OBJ(int);
	EXTL_MUST_BE_CV_OBJ(int*);
	EXTL_MUST_BE_CV_OBJ(int[10]);
	EXTL_MUST_NOT_BE_CV_OBJ(void);
	EXTL_MUST_NOT_BE_CV_OBJ(int &);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
