/* ///////////////////////////////////////////////////////////////////////
 * File:		remove_ref_test.h		
 *
 * Created:		08.02.12			
 * Updated:		08.07.13
 *
 * Brief: remove_ref unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_REMOVE_REF_H
#	error This file must be included of remove_ref.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void remove_ref_test()
{
	EXTL_MUST_NOT_BE_REF(EXTL_REMOVE_REF(int &));
	EXTL_MUST_NOT_BE_REF(EXTL_REMOVE_REF(int const&));
	EXTL_MUST_NOT_BE_REF(EXTL_REMOVE_REF(int volatile&));
	EXTL_MUST_NOT_BE_REF(EXTL_REMOVE_REF(int const volatile &));
	EXTL_MUST_NOT_BE_REF(EXTL_REMOVE_REF(int *&));

}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
