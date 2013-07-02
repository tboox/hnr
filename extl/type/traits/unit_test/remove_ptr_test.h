/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_ptr_test.h		
 *
 * Created:		08.02.12			
 * Updated:		08.07.13
 *
 * Brief: remove_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_PTR_H
#	error This file must be included of remove_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void remove_ptr_test()
{
#ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
	EXTL_MUST_NOT_BE_PTR(EXTL_REMOVE_PTR(int *));
	EXTL_MUST_NOT_BE_PTR(EXTL_REMOVE_PTR(int *const));
	EXTL_MUST_NOT_BE_PTR(EXTL_REMOVE_PTR(int const*));
	EXTL_MUST_NOT_BE_PTR(EXTL_REMOVE_PTR(int volatile*));
	EXTL_MUST_NOT_BE_PTR(EXTL_REMOVE_PTR(int const volatile *));
	EXTL_MUST_NOT_BE_PTR(EXTL_REMOVE_PTR(void *));

	EXTL_MUST_BE_PTR(EXTL_REMOVE_PTR(int **));
#else
	EXTL_REMOVE_PTR(int *) i1 = 10;
	EXTL_REMOVE_PTR(int *const) i2 = 10;
	EXTL_REMOVE_PTR(int const*) i3 = 10;
	EXTL_REMOVE_PTR(int volatile*) i4 = 10;
	EXTL_REMOVE_PTR(int const volatile *) i5 = 10;
	EXTL_REMOVE_PTR(int **) p = NULL;
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
