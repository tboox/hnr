/* ///////////////////////////////////////////////////////////////////////
 * File:		add_ptr_test.h		
 *
 * Created:		08.02.12					
 * Updated:		08.07.09	
 *
 * Brief: add_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_ADD_PTR_H
#	error This file must be included of add_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void add_ptr_test()
{
#ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(int));
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(int const));

#	ifndef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(int &));
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(int const&));
#	endif

	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(int *));
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(int const*));
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(int *const));
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(int [10]));

	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(void));
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(void const));
	EXTL_MUST_BE_PTR(EXTL_ADD_PTR(void const volatile));
#else
	int i;
	int* p1;
	int const* p2;
	EXTL_ADD_PTR(int) i1 = &i;
	EXTL_ADD_PTR(int const) i2 = &i;
#	ifndef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
	EXTL_ADD_PTR(int &) i3 = &i;
	EXTL_ADD_PTR(int const&) i4 = &i;
#	endif
	EXTL_ADD_PTR(int *) i5 = &p1;
	EXTL_ADD_PTR(int const*) i6 = &p2;
	EXTL_ADD_PTR(void) i7 = NULL;
	EXTL_ADD_PTR(void const) i8 = NULL;
	EXTL_ADD_PTR(void const volatile) i9 = NULL;
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
