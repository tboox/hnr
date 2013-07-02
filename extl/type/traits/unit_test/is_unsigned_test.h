/* ///////////////////////////////////////////////////////////////////////
 * File:		is_unsigned_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: is_unsigned unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_UNSIGNED_H
#	error This file must be included of is_unsigned.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_unsigned_test()
{
	EXTL_MUST_BE_UNSIGNED(e_uint8_t);
	EXTL_MUST_BE_UNSIGNED(e_uint64_t);
	EXTL_MUST_BE_UNSIGNED(e_uint8_t);
	EXTL_MUST_NOT_BE_UNSIGNED(int);
	EXTL_MUST_NOT_BE_UNSIGNED(signed int);
	EXTL_MUST_NOT_BE_UNSIGNED(double);
	EXTL_MUST_NOT_BE_UNSIGNED(char);
	EXTL_MUST_NOT_BE_UNSIGNED(e_int32_t);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
