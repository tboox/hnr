/* ///////////////////////////////////////////////////////////////////////
 * File:		is_mem_obj_ptr_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.13	
 *
 * Brief: is_mem_obj_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_H
#	error This file must be included of is_mem_obj_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct is_mem_obj_ptr_test
{
	is_mem_obj_ptr_test()
	{
#if !defined(EXTL_COMPILER_IS_BORLAND) || !(__BORLANDC__ < 0x600)
		EXTL_MUST_BE_CV_MEM_OBJ_PTR(int is_mem_obj_ptr_test::*);
		EXTL_MUST_BE_CV_MEM_OBJ_PTR(void* is_mem_obj_ptr_test::*);
		EXTL_MUST_BE_CV_MEM_OBJ_PTR(int* is_mem_obj_ptr_test::*);
		EXTL_MUST_BE_CV_MEM_OBJ_PTR(char is_mem_obj_ptr_test::*);

		EXTL_MUST_NOT_BE_CV_MEM_OBJ_PTR(char (is_mem_ptr_test::*)());
		EXTL_MUST_NOT_BE_CV_MEM_OBJ_PTR(void);
		EXTL_MUST_NOT_BE_CV_MEM_OBJ_PTR(int *);
		EXTL_MUST_NOT_BE_CV_MEM_OBJ_PTR(int &);
		EXTL_MUST_NOT_BE_CV_MEM_OBJ_PTR(int [10]);
		EXTL_MUST_NOT_BE_CV_MEM_OBJ_PTR(void *);
#endif
	}
};

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
