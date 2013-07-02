/* ///////////////////////////////////////////////////////////////////////
 * File:		add_volatile_test.h		
 *
 * Created:		08.02.12					
 * Updated:		08.07.09	
 *
 * Brief: add_volatile unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_ADD_VOLATILE_H
#	error This file must be included of add_volatile.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void add_volatile_test()
{
#ifdef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
	EXTL_MUST_BE_VOLATILE(EXTL_ADD_VOLATILE(int));
	EXTL_MUST_BE_VOLATILE(EXTL_ADD_VOLATILE(int const));
	EXTL_MUST_BE_VOLATILE(EXTL_ADD_VOLATILE(int volatile));
	EXTL_MUST_BE_VOLATILE(EXTL_ADD_VOLATILE(int [10]));
	EXTL_MUST_BE_VOLATILE(EXTL_ADD_VOLATILE(int (*)()));
	EXTL_MUST_BE_VOLATILE(EXTL_ADD_VOLATILE(int *)); /* int *volatile */
	EXTL_MUST_BE_VOLATILE(EXTL_ADD_VOLATILE(void *));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_ADD_VOLATILE(int &));

#	ifdef EXTL_CV_VOID_SPEC_SUPPORT
	EXTL_MUST_BE_VOLATILE(EXTL_ADD_VOLATILE(void));
#	else
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_ADD_VOLATILE(void));
#	endif
#else
	// I haven't good idea about validating whether volatile qualification has been added.
	// ... 
#endif
}


/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
