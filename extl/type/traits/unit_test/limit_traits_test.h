/* ///////////////////////////////////////////////////////////////////////
 * File:		limit_traits_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: limit_traits_test unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_LIMIT_TRAITS_H
#	error This file must be included of limit_traits_test.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void limit_traits_test()
{
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_int8_t) == EXTL_LIMIT_TRAITS_SINT8_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_int8_t) == EXTL_LIMIT_TRAITS_SINT8_MAX);

	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_uint8_t) == EXTL_LIMIT_TRAITS_UINT8_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_uint8_t) == EXTL_LIMIT_TRAITS_UINT8_MAX);

	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_int16_t) == EXTL_LIMIT_TRAITS_SINT16_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_int16_t) == EXTL_LIMIT_TRAITS_SINT16_MAX);

	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_uint16_t) == EXTL_LIMIT_TRAITS_UINT16_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_uint16_t) == EXTL_LIMIT_TRAITS_UINT16_MAX);

	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_int32_t) == EXTL_LIMIT_TRAITS_SINT32_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_int32_t) == EXTL_LIMIT_TRAITS_SINT32_MAX);

	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_uint32_t) == EXTL_LIMIT_TRAITS_UINT32_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_uint32_t) == EXTL_LIMIT_TRAITS_UINT32_MAX);

#	if defined(EXTL_64BIT_INT_SUPPORT) && defined(EXTL_MEMBER_CONSTANT_64BIT_SUPPORT)
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_int64_t) == EXTL_LIMIT_TRAITS_SINT64_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_int64_t) == EXTL_LIMIT_TRAITS_SINT64_MAX);

	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_uint64_t) == EXTL_LIMIT_TRAITS_UINT64_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_uint64_t) == EXTL_LIMIT_TRAITS_UINT64_MAX);
#	endif

	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(e_char_t) == EXTL_LIMIT_TRAITS_SINT8_MIN);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(e_char_t) == EXTL_LIMIT_TRAITS_SINT8_MAX);

#ifdef EXTL_NATIVE_BOOL_SUPPORT
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MIN(bool) == false);
	EXTL_STATIC_ASSERT(EXTL_LIMIT_TRAITS_MAX(bool) == true);
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
