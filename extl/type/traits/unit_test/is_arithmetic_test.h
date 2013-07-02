/* ///////////////////////////////////////////////////////////////////////
 * File:		is_arithmetic_test.h		
 *
 * Created:		08.02.17					
 * Updated:		08.07.09	
 *
 * Brief: is_arithmetic unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_ARITHMETIC_H
#	error This file must be included of is_arithmetic.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_arithmetic_test()
{
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned char);
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned short);
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned int);
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned long);

	EXTL_MUST_BE_CV_ARITHMETIC(signed char);
	EXTL_MUST_BE_CV_ARITHMETIC(signed short);
	EXTL_MUST_BE_CV_ARITHMETIC(signed int);
	EXTL_MUST_BE_CV_ARITHMETIC(signed long);

	EXTL_MUST_BE_CV_ARITHMETIC(short);
	EXTL_MUST_BE_CV_ARITHMETIC(int);
	EXTL_MUST_BE_CV_ARITHMETIC(long);
	EXTL_MUST_BE_CV_ARITHMETIC(char);

#	ifdef EXTL_NATIVE_BOOL_SUPPORT
	EXTL_MUST_BE_CV_ARITHMETIC(bool);
#	endif

#	ifdef EXTL_NATIVE_WCHAR_T_SUPPORT
	EXTL_MUST_BE_CV_ARITHMETIC(wchar_t);
#	endif

#	ifdef EXTL_08BIT_ARITHMETIC_IS___int8
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned __int8);
	EXTL_MUST_BE_CV_ARITHMETIC(signed __int8);
	EXTL_MUST_BE_CV_ARITHMETIC(__int8);
#	endif

#	ifdef EXTL_16BIT_ARITHMETIC_IS___int16
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned __int16);
	EXTL_MUST_BE_CV_ARITHMETIC(signed __int16);
	EXTL_MUST_BE_CV_ARITHMETIC(__int16);
#	endif

#	ifdef EXTL_32BIT_ARITHMETIC_IS___int32
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned __int32);
	EXTL_MUST_BE_CV_ARITHMETIC(signed __int32);
	EXTL_MUST_BE_CV_ARITHMETIC(__int32);
#	endif

#	ifdef EXTL_64BIT_ARITHMETIC_IS___int64
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned __int64);
	EXTL_MUST_BE_CV_ARITHMETIC(signed __int64);
	EXTL_MUST_BE_CV_ARITHMETIC(__int64);
#	endif

#	ifdef EXTL_64BIT_ARITHMETIC_IS_long_long
	EXTL_MUST_BE_CV_ARITHMETIC(unsigned long long);
	EXTL_MUST_BE_CV_ARITHMETIC(signed long long);
	EXTL_MUST_BE_CV_ARITHMETIC(long long);
#	endif

	EXTL_MUST_BE_CV_ARITHMETIC(float);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

