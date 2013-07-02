/* ///////////////////////////////////////////////////////////////////////
 * File:		is_mem_ptr_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.09	
 *
 * Brief: is_mem_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_MEM_PTR_H
#	error This file must be included of is_mem_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct is_mem_ptr_test
{
	is_mem_ptr_test()
	{
		 EXTL_MUST_BE_CV_MEM_PTR(long is_mem_ptr_test::*);
		 EXTL_MUST_BE_CV_MEM_PTR(void* is_mem_ptr_test::*);
		 EXTL_MUST_BE_CV_MEM_PTR(double* is_mem_ptr_test::*);
		 EXTL_MUST_BE_CV_MEM_PTR(double is_mem_ptr_test::*);

#if (!defined(EXTL_COMPILER_IS_BORLAND) || !(__BORLANDC__ < 0x600)) && \
		!defined(EXTL_COMPILER_IS_VECTORC)
		 EXTL_MUST_BE_CV_MEM_PTR(char (is_mem_ptr_test::*)());
#endif
		
		 EXTL_MUST_NOT_BE_CV_MEM_PTR(void);
		 /* EXTL_MUST_NOT_BE_CV_MEM_PTR(int *); */ // VECTORC: int is_mem_ptr_test::* and int * cannot have only an initialization at same time
		 EXTL_MUST_NOT_BE_CV_MEM_PTR(float *);
		 EXTL_MUST_NOT_BE_CV_MEM_PTR(int &);
		 EXTL_MUST_NOT_BE_CV_MEM_PTR(int [10]);
		 EXTL_MUST_NOT_BE_CV_MEM_PTR(void *);
	}

};

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
