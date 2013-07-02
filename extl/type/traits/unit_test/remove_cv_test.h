/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_cv_test.h		
 *
 * Created:		08.02.12			
 * Updated:		08.07.13
 *
 * Brief: remove_cv unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_CV_H
#	error This file must be included of remove_cv.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void remove_cv_test()
{
#ifdef EXTL_TYPE_TRAITS_IS_CV_SUPPORT
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int volatile));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int const volatile));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int *volatile));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int *const volatile));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int volatile&));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int const*));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int volatile*));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int const volatile *));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(void *));

#	ifndef EXTL_COMPILER_IS_DMC
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int volatile[10]));
	EXTL_MUST_NOT_BE_CV(EXTL_REMOVE_CV(int const[10]));
#	endif
#else
	EXTL_REMOVE_CV(int const) i1 = 10;
	EXTL_REMOVE_CV(int const volatile) i2 = 10;
	EXTL_REMOVE_CV(int *volatile) i3 = &i1;
	EXTL_REMOVE_CV(int *const) i4 = &i1;
	EXTL_REMOVE_CV(int const&) i5 = i1;
	EXTL_REMOVE_CV(int const*) i6 = &i1;
	EXTL_REMOVE_CV(int volatile*) i7 = &i1;
	EXTL_REMOVE_CV(int const volatile *) i8 = NULL;
	EXTL_REMOVE_CV(void *) i9 = NULL;

	i1 = 10;
	i2 = 10;
	i3 = &i1;
	i4 = &i1;
	i6 = &i1;
	i7 = NULL;
	i8 = NULL;

	// I haven't good idea about validating whether volatile qualification has been removed.
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
