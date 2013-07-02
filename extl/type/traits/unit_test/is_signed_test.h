/* ///////////////////////////////////////////////////////////////////////
 * File:		is_signed_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: is_signed unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_SIGNED_H
#	error This file must be included of is_signed.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_signed_test()
{
	EXTL_MUST_BE_SIGNED(int);
	EXTL_MUST_BE_SIGNED(char);
	EXTL_MUST_BE_SIGNED(e_sint8_t);
	EXTL_MUST_BE_SIGNED(e_sint64_t);
	EXTL_MUST_BE_SIGNED(e_int32_t);
	EXTL_MUST_NOT_BE_SIGNED(int*);
	EXTL_MUST_NOT_BE_SIGNED(unsigned int);
	EXTL_MUST_NOT_BE_SIGNED(double);
	EXTL_MUST_NOT_BE_SIGNED(e_ulong_t);
	EXTL_MUST_NOT_BE_SIGNED(e_uint8_t);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
