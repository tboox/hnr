/* ///////////////////////////////////////////////////////////////////////
 * File:		add_const_test.h		
 *
 * Created:		08.02.12					
 * Updated:		08.07.09	
 *
 * Brief: add_const unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_ADD_CONST_H
#	error This file must be included of add_const.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void add_const_test()
{
#ifdef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
	EXTL_MUST_BE_CONST(EXTL_ADD_CONST(int));
	EXTL_MUST_BE_CONST(EXTL_ADD_CONST(int const));
	EXTL_MUST_BE_CONST(EXTL_ADD_CONST(int volatile));
	EXTL_MUST_BE_CONST(EXTL_ADD_CONST(int [10]));
	EXTL_MUST_BE_CONST(EXTL_ADD_CONST(int (*)()));
	EXTL_MUST_BE_CONST(EXTL_ADD_CONST(int *)); /* int *const */
	EXTL_MUST_BE_CONST(EXTL_ADD_CONST(void *));
	EXTL_MUST_NOT_BE_CONST(EXTL_ADD_CONST(int &));

#	ifdef EXTL_CV_VOID_SPEC_SUPPORT
	EXTL_MUST_BE_CONST(EXTL_ADD_CONST(void));
#	else
	EXTL_MUST_NOT_BE_CONST(EXTL_ADD_CONST(void));
#	endif
#else
	// I haven't good idea about validating whether const qualification has been added.
	// ... 
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
