/* ///////////////////////////////////////////////////////////////////////
 * File:		type_size_test.h		
 *
 * Created:		08.03.20					
 * Updated:		08.07.09
 *
 * Brief: type size unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_TYPE_DEF_TEST_H
#define EXTL_TYPE_DEF_TEST_H

#ifndef EXTL_TYPE_DEF_H
#	error This file must be included of typedef.h
#endif

#ifndef EXTL_STATIC_ASSERT
#	error This file need EXTL_STATIC_ASSERT.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void types_size_checker()
{
	/* Char types */
	EXTL_STATIC_ASSERT(sizeof(e_char_t)	>= 1);
	EXTL_STATIC_ASSERT(sizeof(e_wchar_t)	>= 2);

#ifdef EXTL_UNICODE
	EXTL_STATIC_ASSERT(sizeof(e_tchar_t)	>= 2);
#else
	EXTL_STATIC_ASSERT(sizeof(e_tchar_t)	>= 1);
#endif
	/* 8-bit types */
	EXTL_STATIC_ASSERT(sizeof(e_int8_t)	== 1);
	EXTL_STATIC_ASSERT(sizeof(e_sint8_t)	== sizeof(e_int8_t));
	EXTL_STATIC_ASSERT(sizeof(e_uint8_t)	== sizeof(e_int8_t));
	/* 16-bit types */
	EXTL_STATIC_ASSERT(sizeof(e_int16_t)  == 2);
	EXTL_STATIC_ASSERT(sizeof(e_sint16_t) == sizeof(e_int16_t));
	EXTL_STATIC_ASSERT(sizeof(e_uint16_t) == sizeof(e_int16_t));
	/* 32-bit types */
	EXTL_STATIC_ASSERT(sizeof(e_int32_t)  == 4);
	EXTL_STATIC_ASSERT(sizeof(e_sint32_t) == sizeof(e_int32_t));
	EXTL_STATIC_ASSERT(sizeof(e_uint32_t) == sizeof(e_int32_t));
	/* 64-bit types */
#ifdef EXTL_64BIT_INT_SUPPORT
	EXTL_STATIC_ASSERT(sizeof(e_int64_t)  == 8);
	EXTL_STATIC_ASSERT(sizeof(e_sint64_t) == sizeof(e_int64_t));
	EXTL_STATIC_ASSERT(sizeof(e_uint64_t) == sizeof(e_int64_t));
#endif 
	/* Integer types */
	EXTL_STATIC_ASSERT(sizeof(e_int_t)    >= 1);
	EXTL_STATIC_ASSERT(sizeof(e_sint_t)   == sizeof(e_int_t));
	EXTL_STATIC_ASSERT(sizeof(e_uint_t)   == sizeof(e_int_t));
	EXTL_STATIC_ASSERT(sizeof(e_long_t)   >= sizeof(e_int_t));
	EXTL_STATIC_ASSERT(sizeof(e_ulong_t)  == sizeof(e_long_t));

	/* byte type */
	EXTL_STATIC_ASSERT(sizeof(e_byte_t)   == 1);
	/* Boolean type */
	EXTL_STATIC_ASSERT(sizeof(e_bool_t)   >= 1);
	/* other types */
	EXTL_STATIC_ASSERT(sizeof(e_size_t)   >= 1);
	EXTL_STATIC_ASSERT(sizeof(e_ptrdiff_t)>= 1);
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_DEF_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
