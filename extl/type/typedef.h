/* ///////////////////////////////////////////////////////////////////////
 * File:		typedef.h		
 *
 * Created:		08.02.02					
 * Updated:		08.07.09	
 *
 * Brief: The type definition
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_DEF_H
#define EXTL_TYPE_DEF_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h" 
#include "../utility/static_assert.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/* 8-bit */
#ifdef EXTL_8BIT_INT_SUPPORT
	typedef EXTL_SI08_BASE_TYPE		e_int8_t;
	typedef EXTL_SI08_BASE_TYPE		e_sint8_t;
	typedef EXTL_UI08_BASE_TYPE		e_uint8_t;
	typedef e_uint8_t				e_byte_t;
#else 
#	error Extl requires 8-bit integer support.
#endif 

/* 16-bit */
#ifdef EXTL_16BIT_INT_SUPPORT
	typedef	EXTL_SI16_BASE_TYPE		e_int16_t;
	typedef	EXTL_SI16_BASE_TYPE		e_sint16_t;
	typedef	EXTL_UI16_BASE_TYPE		e_uint16_t;
#else 
#	error Extl requires 16-bit integer support.
#endif 

/* 32-bit */
#ifdef EXTL_32BIT_INT_SUPPORT
	typedef	EXTL_SI32_BASE_TYPE		e_int32_t;
	typedef	EXTL_SI32_BASE_TYPE		e_sint32_t;
	typedef	EXTL_UI32_BASE_TYPE		e_uint32_t;
#else 
#	error Extl requires 32-bit integer support.
#endif 

/* 64-bit */
#ifdef EXTL_64BIT_INT_SUPPORT
	typedef	EXTL_SI64_BASE_TYPE		e_int64_t;
	typedef	EXTL_SI64_BASE_TYPE		e_sint64_t;
	typedef	EXTL_UI64_BASE_TYPE		e_uint64_t;
#endif 

	typedef	short					e_short_t;
	typedef	int						e_int_t; 
	typedef	signed int				e_sint_t;
	typedef	unsigned int			e_uint_t; 
	typedef	long					e_long_t; 
	typedef	unsigned long			e_ulong_t;

/* e_bool_t */
#ifdef EXTL_NATIVE_BOOL_SUPPORT
	typedef	bool					e_bool_t;
#	define	e_true_v				(true)
#	define	e_false_v				(false)
#else
	typedef	unsigned int			e_bool_t;
#	define	e_true_v				(1)
#	define	e_false_v				(0)
#endif

/* e_float_t */
	typedef double					e_float_t;

/* e_wchar_t */
#if defined(EXTL_NATIVE_WCHAR_T_SUPPORT) || \
		defined(EXTL_TYPEDEF_WCHAR_T_SUPPORT)
	typedef	wchar_t					e_wchar_t;
#else 
	typedef	unsigned short			e_wchar_t;
#endif

/* e_char_t */
	typedef	char					e_char_t;

/* e_tchar_t */
#ifdef EXTL_UNICODE
	typedef	e_wchar_t				e_tchar_t;
#else 
	typedef	e_char_t				e_tchar_t;
#endif

/* e_size_t */
#ifdef _SIZE_T_DEFINED
	typedef	size_t					e_size_t;
#else
	typedef	unsigned int			e_size_t;
#endif

/* e_ptrdiff_t */
#ifdef _PTRDIFF_T_DEFINED
	typedef	ptrdiff_t				e_ptrdiff_t;
#else
	typedef	int						e_ptrdiff_t;
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef	EXTL_TYPE_SIZE_TEST_ENABLE
#	include "unit_test/type_size_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_DEF_H */
/* //////////////////////////////////////////////////////////////////// */
