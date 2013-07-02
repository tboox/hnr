/* ///////////////////////////////////////////////////////////////////////
 * File:		add_cv_test.h		
 *
 * Created:		08.02.12					
 * Updated:		08.07.09	
 *
 * Brief: add_cv unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_TYPE_TRAITS_ADD_CV_H
#	error This file must be included of add_cv.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void add_cv_test()
{
#ifdef EXTL_TYPE_TRAITS_IS_CV_SUPPORT
	EXTL_MUST_BE_CV(EXTL_ADD_CV(int));
	EXTL_MUST_BE_CV(EXTL_ADD_CV(int const));
	EXTL_MUST_BE_CV(EXTL_ADD_CV(int volatile));
	EXTL_MUST_BE_CV(EXTL_ADD_CV(int [10]));
	EXTL_MUST_BE_CV(EXTL_ADD_CV(int (*)()));
	EXTL_MUST_BE_CV(EXTL_ADD_CV(int *)); /* int *const volatile */
	EXTL_MUST_BE_CV(EXTL_ADD_CV(void *));
	EXTL_MUST_NOT_BE_CV(EXTL_ADD_CV(int &));

#	ifdef EXTL_CV_VOID_SPEC_SUPPORT
	EXTL_MUST_BE_CV(EXTL_ADD_CV(void));
#	else
	EXTL_MUST_NOT_BE_CV(EXTL_ADD_CV(void));
#	endif
#else
	// I haven't good idea about validating whether cv qualification has been added.
	// ... 
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

