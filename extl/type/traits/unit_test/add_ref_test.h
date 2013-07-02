/* ///////////////////////////////////////////////////////////////////////
 * File:		add_ref_test.h		
 *
 * Created:		08.02.12					
 * Updated:		08.07.09	
 *
 * Brief: add_ref unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_ADD_REF_H
#	error This file must be included of add_ref.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void add_ref_test()
{
	EXTL_MUST_BE_REF(EXTL_ADD_REF(int));
	EXTL_MUST_BE_REF(EXTL_ADD_REF(int const));
	EXTL_MUST_BE_REF(EXTL_ADD_REF(int &));
	EXTL_MUST_BE_REF(EXTL_ADD_REF(int const&));
	EXTL_MUST_BE_REF(EXTL_ADD_REF(void *));

	EXTL_MUST_BE_REF(EXTL_ADD_REF(int *));
	EXTL_MUST_BE_REF(EXTL_ADD_REF(int const*));
	EXTL_MUST_BE_REF(EXTL_ADD_REF(int *const));
	EXTL_MUST_BE_REF(EXTL_ADD_REF(int [10]));

	EXTL_MUST_NOT_BE_REF(EXTL_ADD_REF(void));
	EXTL_MUST_NOT_BE_REF(EXTL_ADD_REF(void const));
	EXTL_MUST_NOT_BE_REF(EXTL_ADD_REF(void const volatile));
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
