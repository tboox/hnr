/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_const_test.h		
 *
 * Created:		08.02.12			
 * Updated:		08.07.13
 *
 * Brief: remove_const unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_CONST_H
#	error This file must be included of remove_const.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void remove_const_test()
{
#ifdef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(int const));
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(int const volatile));
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(int *const));
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(int const&));
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(int const*));
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(int volatile*));
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(int const volatile *));
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(void *));

	// int [10] and int const[10] cannot exist at same time, see also is_const_test.h 
#	if !defined(EXTL_COMPILER_IS_DMC) && !defined(EXTL_COMPILER_IS_VECTORC)
	EXTL_MUST_NOT_BE_CONST(EXTL_REMOVE_CONST(int const[10]));
#	endif
#else
	EXTL_REMOVE_CONST(int const) i1 = 10;
	EXTL_REMOVE_CONST(int const volatile) i2 = 10;
	EXTL_REMOVE_CONST(int *const) i3 = &i1;
	EXTL_REMOVE_CONST(int const&) i4 = i1;
	EXTL_REMOVE_CONST(int const*) i5 = &i1;
	EXTL_REMOVE_CONST(int volatile*) i6 = &i1;
	EXTL_REMOVE_CONST(int const volatile *) i7 = NULL;
	EXTL_REMOVE_CONST(void *) i8 = NULL;

	// Validates whether const qualification has been removed.
	i1 = 10;
	i2 = 10;
	i3 = &i1;
	i5 = &i1;
	i6 = &i1;
	i7 = NULL;
	i8 = NULL;
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
