/* ///////////////////////////////////////////////////////////////////////
 * File:		is_ptr_test.h		
 *
 * Created:		08.02.14				
 * Updated:		08.07.13
 *
 * Brief: is_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_PTR_H
#	error This file must be included of is_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_ptr_test()
{
	EXTL_MUST_BE_CV_PTR(int *);
	EXTL_MUST_BE_CV_PTR(void *);
	EXTL_MUST_BE_CV_PTR(char *);
	EXTL_MUST_BE_CV_PTR(int **);
#if !defined(EXTL_COMPILER_IS_VECTORC)
	EXTL_MUST_BE_CV_PTR(int (*)());
#else
	EXTL_MUST_BE_PTR(int (*)());
#endif
	
	EXTL_MUST_NOT_BE_CV_PTR(int);
	EXTL_MUST_NOT_BE_CV_PTR(int&);
	EXTL_MUST_NOT_BE_CV_PTR(void);
	EXTL_MUST_NOT_BE_CV_PTR(int [10]);

#if (defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER > 1310)) || defined(EXTL_COMPILER_IS_DMC)
	struct is_ptr_test_0;
	EXTL_MUST_NOT_BE_CV_PTR(int (is_ptr_test_0::*)());
	EXTL_MUST_NOT_BE_CV_PTR(int is_ptr_test_0::*);
#endif
}


/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
