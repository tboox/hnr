/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_volatile_test.h		
 *
 * Created:		08.02.12			
 * Updated:		08.07.13
 *
 * Brief: remove_volatile unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_VOLATILE_H
#	error This file must be included of remove_volatile.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void remove_volatile_test()
{
#ifdef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int volatile));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int const volatile));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int *volatile));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int *const volatile));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int volatile&));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int const*));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int volatile*));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int const volatile *));
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(void *));

	// int [10] conflict with int volatile[10], see also is_volatile_test.h 
	#if !defined(EXTL_COMPILER_IS_DMC) && !defined(EXTL_COMPILER_IS_VECTORC)
	EXTL_MUST_NOT_BE_VOLATILE(EXTL_REMOVE_VOLATILE(int volatile[10]));
#	endif
#else
	// I haven't good idea about validating whether volatile qualification has been removed.
	// ... 
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
