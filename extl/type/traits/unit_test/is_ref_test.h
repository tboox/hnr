/* ///////////////////////////////////////////////////////////////////////
 * File:		is_ref_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: is_ref unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_REF_H
#	error This file must be included of is_ref.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_ref_test()
{
	EXTL_MUST_BE_CV_REF(int &);
	EXTL_MUST_BE_CV_REF(float &);
	EXTL_MUST_BE_CV_REF(int* &);


	/* note: cannot exclude T[] at VC6.0 */
#ifdef EXTL_COMPILER_IS_MSVC 
#	if (_MSC_VER > 1200)
	EXTL_MUST_NOT_BE_CV_REF(int []);
#	endif
#elif !defined(EXTL_COMPILER_IS_VECTORC) /* VectorC: int* <=>int []  */
	EXTL_MUST_NOT_BE_CV_REF(int []);
#endif

	EXTL_MUST_NOT_BE_CV_REF(int);
	EXTL_MUST_NOT_BE_CV_REF(int [10]);
	EXTL_MUST_NOT_BE_CV_REF(int *); 
	EXTL_MUST_NOT_BE_CV_REF(void);

	typedef int (is_func_test_0)();
	EXTL_MUST_NOT_BE_REF(is_func_test_0);
	

}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

