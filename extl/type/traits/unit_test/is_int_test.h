/* ///////////////////////////////////////////////////////////////////////
 * File:		is_int_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.09	
 *
 * Brief: is_int unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_INT_H
#	error This file must be included of is_int.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_int_test()
{
	EXTL_MUST_BE_CV_INT(unsigned char);
	EXTL_MUST_BE_CV_INT(unsigned short);
	EXTL_MUST_BE_CV_INT(unsigned int);
	EXTL_MUST_BE_CV_INT(unsigned long);

	EXTL_MUST_BE_CV_INT(signed char);
	EXTL_MUST_BE_CV_INT(signed short);
	EXTL_MUST_BE_CV_INT(signed int);
	EXTL_MUST_BE_CV_INT(signed long);

	EXTL_MUST_BE_CV_INT(short);
	EXTL_MUST_BE_CV_INT(int);
	EXTL_MUST_BE_CV_INT(long);
	EXTL_MUST_BE_CV_INT(char);

#	ifdef EXTL_NATIVE_BOOL_SUPPORT
	EXTL_MUST_BE_CV_INT(bool);
#	endif

#	ifdef EXTL_NATIVE_WCHAR_T_SUPPORT
	EXTL_MUST_BE_CV_INT(wchar_t);
#	endif

#	ifdef EXTL_08BIT_INT_IS___int8
	EXTL_MUST_BE_CV_INT(unsigned __int8);
	EXTL_MUST_BE_CV_INT(signed __int8);
	EXTL_MUST_BE_CV_INT(__int8);
#	endif

#	ifdef EXTL_16BIT_INT_IS___int16
	EXTL_MUST_BE_CV_INT(unsigned __int16);
	EXTL_MUST_BE_CV_INT(signed __int16);
	EXTL_MUST_BE_CV_INT(__int16);
#	endif

#	ifdef EXTL_32BIT_INT_IS___int32
	EXTL_MUST_BE_CV_INT(unsigned __int32);
	EXTL_MUST_BE_CV_INT(signed __int32);
	EXTL_MUST_BE_CV_INT(__int32);
#	endif

#	ifdef EXTL_64BIT_INT_IS___int64
	EXTL_MUST_BE_CV_INT(unsigned __int64);
	EXTL_MUST_BE_CV_INT(signed __int64);
	EXTL_MUST_BE_CV_INT(__int64);
#	endif

#	ifdef EXTL_64BIT_INT_IS_long_long
	EXTL_MUST_BE_CV_INT(unsigned long long);
	EXTL_MUST_BE_CV_INT(signed long long);
	EXTL_MUST_BE_CV_INT(long long);
#	endif

}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
