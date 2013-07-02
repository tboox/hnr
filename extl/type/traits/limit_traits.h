/* ///////////////////////////////////////////////////////////////////////
 * File:		limit_traits.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: limit_traits traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_LIMIT_TRAITS_H
#define EXTL_TYPE_TRAITS_LIMIT_TRAITS_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_signed.h"
#include "is_unsigned.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

/* minimum and maximum value */
#ifdef EXTL_TYPE_TRAITS_SUPPORT
#	define EXTL_LIMIT_TRAITS_MIN(type)		(EXTL_NS(limit_traits)< type >::min_value)
#	define EXTL_LIMIT_TRAITS_MAX(type)		(EXTL_NS(limit_traits)< type >::max_value)
#else
#	define EXTL_LIMIT_TRAITS_MIN(type)		(0)
#	define EXTL_LIMIT_TRAITS_MAX(type)		(0)
#endif

/* constant suffix */
#define	EXTL_CONST_SINT8_SUFFIX(i)				(i)
#define	EXTL_CONST_UINT8_SUFFIX(i)				(i ## U)
#define EXTL_CONST_SINT16_SUFFIX(i)				(i)
#define EXTL_CONST_UINT16_SUFFIX(i)				(i ## U)
#define EXTL_CONST_SINT32_SUFFIX(i)				(i ## L)
#define EXTL_CONST_UINT32_SUFFIX(i)				(i ## UL)
#if	((defined(EXTL_COMPILER_IS_BORLAND) &&  __BORLANDC__ >= 0x0582) || \
		defined(EXTL_COMPILER_IS_DMC) || \
			defined(EXTL_COMPILER_IS_GCC))
#	define EXTL_CONST_SINT64_SUFFIX(i)			(i ## LL)
#	define EXTL_CONST_UINT64_SUFFIX(i)			(i ## ULL)
#elif	(defined(EXTL_COMPILER_IS_BORLAND) || \
        defined(EXTL_COMPILER_IS_INTEL) || \
        defined(EXTL_COMPILER_IS_MSVC) || \
		defined(EXTL_COMPILER_IS_VECTORC) || \
        defined(EXTL_COMPILER_IS_WATCOM))
#	define EXTL_CONST_SINT64_SUFFIX(i)			(i ## L)
#	define EXTL_CONST_UINT64_SUFFIX(i)			(i ## UL)
#else
#	error Compiler is not discriminated.
#endif 

/* Numerical limit range */
#define	EXTL_LIMIT_TRAITS_SINT8_MIN		(- EXTL_CONST_SINT8_SUFFIX(127) - 1)
#define	EXTL_LIMIT_TRAITS_SINT8_MAX		(+ EXTL_CONST_SINT8_SUFFIX(127))

#define	EXTL_LIMIT_TRAITS_UINT8_MIN		(  EXTL_CONST_UINT8_SUFFIX(0))
#define	EXTL_LIMIT_TRAITS_UINT8_MAX		(  EXTL_CONST_UINT8_SUFFIX(255))

#define	EXTL_LIMIT_TRAITS_SINT16_MIN		(- EXTL_CONST_SINT16_SUFFIX(32767) - 1)
#define	EXTL_LIMIT_TRAITS_SINT16_MAX		(+ EXTL_CONST_SINT16_SUFFIX(32767))

#define	EXTL_LIMIT_TRAITS_UINT16_MIN		(  EXTL_CONST_UINT16_SUFFIX(0))
#define	EXTL_LIMIT_TRAITS_UINT16_MAX		(  EXTL_CONST_UINT16_SUFFIX(65535))

#define	EXTL_LIMIT_TRAITS_SINT32_MIN		(- EXTL_CONST_SINT32_SUFFIX(2147483647) - 1)
#define	EXTL_LIMIT_TRAITS_SINT32_MAX		(+ EXTL_CONST_SINT32_SUFFIX(2147483647))

#define	EXTL_LIMIT_TRAITS_UINT32_MIN		(  EXTL_CONST_UINT32_SUFFIX(0))
#define	EXTL_LIMIT_TRAITS_UINT32_MAX		(  EXTL_CONST_UINT32_SUFFIX(4294967295))

#define	EXTL_LIMIT_TRAITS_SINT64_MIN		(- EXTL_CONST_SINT64_SUFFIX(9223372036854775807) - 1)
#define	EXTL_LIMIT_TRAITS_SINT64_MAX		(+ EXTL_CONST_SINT64_SUFFIX(9223372036854775807) )

#define	EXTL_LIMIT_TRAITS_UINT64_MIN		(  EXTL_CONST_UINT64_SUFFIX(0) )
#define	EXTL_LIMIT_TRAITS_UINT64_MAX		(  EXTL_CONST_UINT64_SUFFIX(18446744073709551615) )

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

/* pow2 */
template < e_size_t N >
struct limit_traits_pow2
{
#	if defined(EXTL_64BIT_INT_SUPPORT) && !defined(EXTL_COMPILER_IS_BORLAND)
		EXTL_STATIC_MEMBER_CONST(e_uint64_t, value = ((limit_traits_pow2< N - 1 >::value) + (limit_traits_pow2< N - 1 >::value)));
#	else
		EXTL_STATIC_MEMBER_CONST(e_uint32_t, value = ((limit_traits_pow2< N - 1 >::value) + (limit_traits_pow2< N - 1 >::value)));
#	endif
};

EXTL_TEMPLATE_SPECIALISATION
struct limit_traits_pow2< 0 >
{
#	if defined(EXTL_64BIT_INT_SUPPORT) && !defined(EXTL_COMPILER_IS_BORLAND)
		EXTL_STATIC_MEMBER_CONST(e_uint64_t, value = 1);
#	else
		EXTL_STATIC_MEMBER_CONST(e_uint32_t, value = 1);
#	endif
};

#	if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) && \
			!defined(EXTL_COMPILER_IS_VECTORC) && \
			!EXTL_WORKAROUND_BORLAND(==, 0x0564) && \
			defined(EXTL_MEMBER_CONSTANT_64BIT_SUPPORT)
	template < e_bool_t is_signed, e_bool_t is_unsigned >
	struct limit_traits_helper
	{
		template < typename_param_k T >
		struct result
		{
			EXTL_STATIC_MEMBER_CONST(T, bit_count = static_cast<T>(0));
			EXTL_STATIC_MEMBER_CONST(T, min_value = static_cast<T>(0));
			EXTL_STATIC_MEMBER_CONST(T, max_value = static_cast<T>(0)); 
		};
	};
	/* signed */
	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_helper< e_true_v, e_false_v >
	{
		template < typename_param_k T >
		struct result
		{
			EXTL_STATIC_MEMBER_CONST(T, bit_count = static_cast<T>(8 * sizeof(T)));
			// temp_value = 2^(bit_count-2), prevent overflow 
			EXTL_STATIC_MEMBER_CONST(T, temp_value = static_cast<T>(limit_traits_pow2< bit_count - 2 >::value));
			EXTL_STATIC_MEMBER_CONST(T, min_value = static_cast<T>(-temp_value - temp_value));
			EXTL_STATIC_MEMBER_CONST(T, max_value = static_cast<T>((temp_value - 1) + temp_value)); 
		};
	};
	/* unsigned */
	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_helper< e_false_v, e_true_v >
	{
		template < typename_param_k T >
		struct result
		{
			EXTL_STATIC_MEMBER_CONST(T, bit_count = static_cast<T>(8 * sizeof(T)));
			// temp_value = 2^(bit_count-1), prevent overflow 
			EXTL_STATIC_MEMBER_CONST(T, temp_value = static_cast<T>(limit_traits_pow2< bit_count - 1 >::value));
			EXTL_STATIC_MEMBER_CONST(T, min_value = static_cast<T>(0));
			EXTL_STATIC_MEMBER_CONST(T, max_value = static_cast<T>((temp_value-1) + temp_value)); 
		};
	};

	template < typename_param_k T >
	struct limit_traits_impl
		: limit_traits_helper< (is_signed<T>::value), (is_unsigned<T>::value) >::template result<T>
	{
	};

	template < typename_param_k T >
	struct limit_traits
	{
		EXTL_STATIC_MEMBER_CONST(T, min_value = (limit_traits_impl<T>::min_value));
		EXTL_STATIC_MEMBER_CONST(T, max_value = (limit_traits_impl<T>::max_value));
	};

#		ifdef EXTL_NATIVE_BOOL_SUPPORT
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits< bool >
		{
			EXTL_STATIC_MEMBER_CONST(bool, min_value = (false));
			EXTL_STATIC_MEMBER_CONST(bool, max_value = (true));
		};
#		endif
#	else

	template < e_bool_t is_signed, e_bool_t is_unsigned, e_size_t bit_count >
	struct limit_traits_impl
	{
		EXTL_STATIC_MEMBER_CONST(e_uint_t, min_value = 0);
		EXTL_STATIC_MEMBER_CONST(e_uint_t, max_value = 0);
	};

	/* signed */
	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl<e_true_v, e_false_v, 8>
	{
		EXTL_STATIC_MEMBER_CONST(e_sint8_t, min_value = EXTL_LIMIT_TRAITS_SINT8_MIN);
		EXTL_STATIC_MEMBER_CONST(e_sint8_t, max_value = EXTL_LIMIT_TRAITS_SINT8_MAX);
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl<e_true_v, e_false_v, 16>
	{
		EXTL_STATIC_MEMBER_CONST(e_sint16_t, min_value = EXTL_LIMIT_TRAITS_SINT16_MIN);
		EXTL_STATIC_MEMBER_CONST(e_sint16_t, max_value = EXTL_LIMIT_TRAITS_SINT16_MAX);
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl<e_true_v, e_false_v, 32>
	{
		EXTL_STATIC_MEMBER_CONST(e_sint32_t, min_value = EXTL_LIMIT_TRAITS_SINT32_MIN);
		EXTL_STATIC_MEMBER_CONST(e_sint32_t, max_value = EXTL_LIMIT_TRAITS_SINT32_MAX);
	};
#		if defined(EXTL_64BIT_INT_SUPPORT) && defined(EXTL_MEMBER_CONSTANT_64BIT_SUPPORT)
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl<e_true_v, e_false_v, 64>
		{
			EXTL_STATIC_MEMBER_CONST(e_sint64_t, min_value = EXTL_LIMIT_TRAITS_SINT64_MIN);
			EXTL_STATIC_MEMBER_CONST(e_sint64_t, max_value = EXTL_LIMIT_TRAITS_SINT64_MAX);
		};
#		endif

	/* unsigned */
	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl<e_false_v, e_true_v, 8>
	{
		EXTL_STATIC_MEMBER_CONST(e_uint8_t, min_value = EXTL_LIMIT_TRAITS_UINT8_MIN);
		EXTL_STATIC_MEMBER_CONST(e_uint8_t, max_value = EXTL_LIMIT_TRAITS_UINT8_MAX);
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl<e_false_v, e_true_v, 16>
	{
		EXTL_STATIC_MEMBER_CONST(e_uint16_t, min_value = EXTL_LIMIT_TRAITS_UINT16_MIN);
		EXTL_STATIC_MEMBER_CONST(e_uint16_t, max_value = EXTL_LIMIT_TRAITS_UINT16_MAX);
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl<e_false_v, e_true_v, 32>
	{
		EXTL_STATIC_MEMBER_CONST(e_uint32_t, min_value = EXTL_LIMIT_TRAITS_UINT32_MIN);
		EXTL_STATIC_MEMBER_CONST(e_uint32_t, max_value = EXTL_LIMIT_TRAITS_UINT32_MAX);
	};
#		if defined(EXTL_64BIT_INT_SUPPORT) && defined(EXTL_MEMBER_CONSTANT_64BIT_SUPPORT)
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl<e_false_v, e_true_v, 64>
		{
			EXTL_STATIC_MEMBER_CONST(e_uint64_t, min_value = EXTL_LIMIT_TRAITS_UINT64_MIN);
			EXTL_STATIC_MEMBER_CONST(e_uint64_t, max_value = EXTL_LIMIT_TRAITS_UINT64_MAX);
		};
#		endif

	template < typename_param_k T >
	struct limit_traits
	{
		EXTL_STATIC_MEMBER_CONST(T, min_value = (limit_traits_impl	<	(is_signed<T>::value)
																	,	(is_unsigned<T>::value)
																	,	sizeof(T)*8
																	>::min_value));
		EXTL_STATIC_MEMBER_CONST(T, max_value = (limit_traits_impl	<	(is_signed<T>::value)
																	,	(is_unsigned<T>::value)
																	,	sizeof(T)*8
																	>::max_value));
	};

#		ifdef EXTL_NATIVE_BOOL_SUPPORT
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits< bool >
		{
			EXTL_STATIC_MEMBER_CONST(bool, min_value = (false));
			EXTL_STATIC_MEMBER_CONST(bool, max_value = (true));
		};
#		endif

	/*template < typename_param_k T >
	struct limit_traits_impl
	{
		EXTL_STATIC_MEMBER_CONST(T, min_value = static_cast<T>(0));
		EXTL_STATIC_MEMBER_CONST(T, max_value = static_cast<T>(0));
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< unsigned char >
	{
		EXTL_STATIC_MEMBER_CONST(unsigned char, bit_count = static_cast<unsigned char>(8 * sizeof( unsigned char )));
		EXTL_STATIC_MEMBER_CONST(unsigned char, temp_value = static_cast<unsigned char>(limit_traits_pow2< bit_count-1 >::value));
		EXTL_STATIC_MEMBER_CONST(unsigned char, min_value = static_cast<unsigned char>(0));
		EXTL_STATIC_MEMBER_CONST(unsigned char, max_value = static_cast<unsigned char>((temp_value-1)+temp_value)); 
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< unsigned short >
	{
		EXTL_STATIC_MEMBER_CONST(unsigned short, bit_count = static_cast<unsigned short>(8 * sizeof( unsigned short )));
		EXTL_STATIC_MEMBER_CONST(unsigned short, temp_value = static_cast<unsigned short>(limit_traits_pow2< bit_count-1 >::value));
		EXTL_STATIC_MEMBER_CONST(unsigned short, min_value = static_cast<unsigned short>(0));
		EXTL_STATIC_MEMBER_CONST(unsigned short, max_value = static_cast<unsigned short>((temp_value-1)+temp_value)); 
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< unsigned int >
	{
		EXTL_STATIC_MEMBER_CONST(unsigned int, bit_count = static_cast<unsigned int>(8 * sizeof(unsigned int)));
		EXTL_STATIC_MEMBER_CONST(unsigned int, temp_value = static_cast<unsigned int>(limit_traits_pow2< bit_count-1 >::value));
		EXTL_STATIC_MEMBER_CONST(unsigned int, min_value = static_cast<unsigned int>(0));
		EXTL_STATIC_MEMBER_CONST(unsigned int, max_value = static_cast<unsigned int>((temp_value-1)+temp_value)); 
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< unsigned long >
	{
		EXTL_STATIC_MEMBER_CONST(unsigned long, bit_count = static_cast<unsigned long>(8 * sizeof(unsigned long)));
		EXTL_STATIC_MEMBER_CONST(unsigned long, temp_value = static_cast<unsigned long>(limit_traits_pow2< bit_count-1 >::value));
		EXTL_STATIC_MEMBER_CONST(unsigned long, min_value = static_cast<unsigned long>(0));
		EXTL_STATIC_MEMBER_CONST(unsigned long, max_value = static_cast<unsigned long>((temp_value-1)+temp_value)); 
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< signed char >
	{
		EXTL_STATIC_MEMBER_CONST(signed char, bit_count = static_cast<signed char>(8 * sizeof(signed char)));
		EXTL_STATIC_MEMBER_CONST(signed char, temp_value = static_cast<signed char>(limit_traits_pow2< bit_count-2 >::value));
		EXTL_STATIC_MEMBER_CONST(signed char, min_value = static_cast<signed char>(-temp_value-temp_value));
		EXTL_STATIC_MEMBER_CONST(signed char, max_value = static_cast<signed char>((temp_value-1)+temp_value)); 
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< signed short >
	{
		EXTL_STATIC_MEMBER_CONST(signed short, bit_count = static_cast<signed short>(8 * sizeof(signed short)));
		EXTL_STATIC_MEMBER_CONST(signed short, temp_value = static_cast<signed short>(limit_traits_pow2< bit_count-2 >::value));
		EXTL_STATIC_MEMBER_CONST(signed short, min_value = static_cast<signed short>(-temp_value-temp_value));
		EXTL_STATIC_MEMBER_CONST(signed short, max_value = static_cast<signed short>((temp_value-1)+temp_value)); 
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< signed int >
	{
		EXTL_STATIC_MEMBER_CONST(signed int, bit_count = static_cast<signed int>(8 * sizeof(signed int)));
		EXTL_STATIC_MEMBER_CONST(signed int, temp_value = static_cast<signed int>(limit_traits_pow2< bit_count-2 >::value));
		EXTL_STATIC_MEMBER_CONST(signed int, min_value = static_cast<signed int>(-temp_value-temp_value));
		EXTL_STATIC_MEMBER_CONST(signed int, max_value = static_cast<signed int>((temp_value-1)+temp_value)); 
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< signed long >
	{
		EXTL_STATIC_MEMBER_CONST(signed long, bit_count = static_cast<signed long>(8 * sizeof(signed long)));
		EXTL_STATIC_MEMBER_CONST(signed long, temp_value = static_cast<signed long>(limit_traits_pow2< bit_count-2 >::value));
		EXTL_STATIC_MEMBER_CONST(signed long, min_value = static_cast<signed long>(-temp_value-temp_value));
		EXTL_STATIC_MEMBER_CONST(signed long, max_value = static_cast<signed long>((temp_value-1)+temp_value)); 
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct limit_traits_impl< char >
	{
		EXTL_STATIC_MEMBER_CONST(int, bit_count = static_cast<int>(8 * sizeof(char)));
		EXTL_STATIC_MEMBER_CONST(int, temp_value = static_cast<int>(limit_traits_pow2< bit_count-2 >::value));
		EXTL_STATIC_MEMBER_CONST(int, min_value = static_cast<int>(-temp_value-temp_value));
		EXTL_STATIC_MEMBER_CONST(int, max_value = static_cast<int>((temp_value-1)+temp_value)); 
	};

#		ifdef EXTL_NATIVE_BOOL_SUPPORT
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< bool >
		{
			EXTL_STATIC_MEMBER_CONST(bool, min_value = (false));
			EXTL_STATIC_MEMBER_CONST(bool, max_value = (true)); 
		};
#		endif

#		ifdef EXTL_08BIT_INT_IS___int8
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< unsigned __int8 >
		{
			EXTL_STATIC_MEMBER_CONST(unsigned __int8, min_value = EXTL_LIMIT_TRAITS_UINT8_MIN);
			EXTL_STATIC_MEMBER_CONST(unsigned __int8, max_value = EXTL_LIMIT_TRAITS_UINT8_MAX); 
		};

		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< signed __int8 >
		{
			EXTL_STATIC_MEMBER_CONST(signed __int8, min_value = EXTL_LIMIT_TRAITS_SINT8_MIN);
			EXTL_STATIC_MEMBER_CONST(signed __int8, max_value = EXTL_LIMIT_TRAITS_SINT8_MAX); 
		};
#		endif

#		ifdef EXTL_016BIT_INT_IS___int16
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< unsigned __int16 >
		{
			EXTL_STATIC_MEMBER_CONST(unsigned __int16, min_value = EXTL_LIMIT_TRAITS_UINT16_MIN);
			EXTL_STATIC_MEMBER_CONST(unsigned __int16, max_value = EXTL_LIMIT_TRAITS_UINT16_MAX); 
		};

		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< signed __int16 >
		{
			EXTL_STATIC_MEMBER_CONST(signed __int16, min_value = EXTL_LIMIT_TRAITS_SINT16_MIN);
			EXTL_STATIC_MEMBER_CONST(signed __int16, max_value = EXTL_LIMIT_TRAITS_SINT16_MAX); 
		};
#		endif

#		ifdef EXTL_032BIT_INT_IS___int32
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< unsigned __int32 >
		{
			EXTL_STATIC_MEMBER_CONST(unsigned __int32, min_value = EXTL_LIMIT_TRAITS_UINT32_MIN);
			EXTL_STATIC_MEMBER_CONST(unsigned __int32, max_value = EXTL_LIMIT_TRAITS_UINT32_MAX); 
		};

		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< signed __int32 >
		{
			EXTL_STATIC_MEMBER_CONST(signed __int32, min_value = EXTL_LIMIT_TRAITS_SINT32_MIN);
			EXTL_STATIC_MEMBER_CONST(signed __int32, max_value = EXTL_LIMIT_TRAITS_SINT32_MAX); 
		};
#		endif

#		ifdef EXTL_064BIT_INT_IS___int64
		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< unsigned __int64 >
		{
			EXTL_STATIC_MEMBER_CONST(unsigned __int64, min_value = EXTL_LIMIT_TRAITS_UINT64_MIN);
			EXTL_STATIC_MEMBER_CONST(unsigned __int64, max_value = EXTL_LIMIT_TRAITS_UINT64_MAX); 
		};

		EXTL_TEMPLATE_SPECIALISATION
		struct limit_traits_impl< signed __int64 >
		{
			EXTL_STATIC_MEMBER_CONST(signed __int64, min_value = EXTL_LIMIT_TRAITS_SINT64_MIN);
			EXTL_STATIC_MEMBER_CONST(signed __int64, max_value = EXTL_LIMIT_TRAITS_SINT64_MAX); 
		};

#		endif

	template < typename_param_k T >
	struct limit_traits
	{
		EXTL_STATIC_MEMBER_CONST(T, min_value = (limit_traits_impl<T>::min_value));
		EXTL_STATIC_MEMBER_CONST(T, max_value = (limit_traits_impl<T>::max_value));
	};*/

#	endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/limit_traits_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_TRAITS_LIMIT_TRAITS_H */
