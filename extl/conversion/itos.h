/* ///////////////////////////////////////////////////////////////////////
 * File:		itos.h		
 *
 * Created:		08.03.03				
 * Updated:		08.05.09
 *
 * Brief: integer ==> string 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONVERSION_ITOS_H
#define EXTL_CONVERSION_ITOS_H

/*!\file itos.h
 * \brief integer ==> string 
 * 
 * - itos<>
 *   - Automatic symbol identification 
 *   - Automatic type identification 
 *   - support 64-bit integer conversion
 *   - support static array size determination 
 *   - Multi-band conversion ==> Default: 10
 *     - itos<10> or itos Decimal(Default)
 *     - itos<16> Hexadecimal 
 *     - itos<2>  Binary 
 *
 * - uitos/sitos
 *   - Automatic type identification 
 *   - support 64-bit integer conversion
 *   - support static array size determination 
 *   - Multi-band conversion ==> Default: 10
 *   - Note: needs provide conversion buffer
 * 
 * - i2s<> shim
 *   - Note: It's rather dangerous because the life cycle of it's buffer is so short
 *   - eg: 
 *     - e_char_t *p = i2s<e_char_t>(0);
 *     - printf(p);									<== Undefined!
 *     - printf(i2s<e_char_t>(0));					<== Safe!
 *
 * Compatibility:
 * - WATCOM: Only support uitos(),sitos()
 * - VC6.0: Only support itos()
 * - VECTORC: When compiling i2s<> in unicode character-set will link failure
 *
 */
#ifndef __cplusplus
#	error itos.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */

#include "prefix.h"
#include "../type/traits/limit_traits.h"
#include "../type/traits/is_signed.h"
#include "../type/traits/is_unsigned.h"
#include "../memory/stack_buffer.h"

#ifdef EXTL_CONVERSION_ITOS_TEST_ENABLE
#	include "../counter/counter.h"
#	ifdef EXTL_COMPILER_IS_GCC
#		define ultoa_test	_ultot
#	else
#		define ultoa_test	_ultot
#	endif
#	define ltoa_test	_ltot
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* itos<N>() support */
#ifdef EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT
#	undef EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT
#endif

#if !defined(EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST) && \
			defined(EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT)
#	define EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT
#endif

/* The maximum number of the string buffer */
#define EXTL_ITOS_MAX_CHAR_NUM	(64 + 1)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE 

/* Search Table */
template < typename_param_k C >
#ifdef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST /* WATCOM */
inline C const* get_digit_char(C*)
#else
inline C const* get_digit_char()
#endif
{
    static C const s_char_table[31] =
    {
		  'F', 'E', 'D', 'C', 'B', 'A', '9', '8', '7', '6', '5', '4', '3', '2', '1'	/* Negative integer */
		, '0'
		, '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'	/* Positive integer */
    };

    return s_char_table + 15;
}

/* ///////////////////////////////////////////////////////////////////////
 * unsigned integer conversion implementaion
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template < typename_param_k I, typename_param_k C, e_size_t N = 10 >
#else
template < typename_param_k I, typename_param_k C, e_size_t N >
#endif
struct uitos_impl
{
	static inline C const* convert(I num, C* buf, e_size_t const& n)
	{
		EXTL_MUST_BE_UNSIGNED(I);

		EXTL_ASSERT(NULL != buf);
		if(NULL == buf) return NULL;

		EXTL_ASSERT(n >= 2);
		if(n < 2)
		{
			buf[0] = static_cast<C>('\0');
			return buf;
		}

		/* convert from the tail */
		C* p = buf + n - 1;
		*p = 0;

		do
		{
			I index = static_cast<I>(num % static_cast<I>(N));
			num = static_cast<I>(num / static_cast<I>(N));

			--p;

		#ifdef EXTL_COMPILER_IS_WATCOM
			*p = get_digit_char(static_cast<C*>(NULL))[index];
		#else
		#	ifdef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
			*p = get_digit_char<C>(static_cast<C*>(NULL))[index];
		#	else
			*p = get_digit_char<C>()[index];
		#	endif
		#endif
			
		}
		while (num != 0);

		EXTL_ASSERT((p >= buf));
		
		return p;
	}

	static inline C const* convert(I num, C* buf, e_size_t const& n, e_size_t& result_count)
	{
		C const* p = convert(num, buf, n);
		result_count = n - (p - buf + 1);
		return p;
	}
};

/* ///////////////////////////////////////////////////////////////////////
 * signed integer conversion implementaion
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template < typename_param_k I, typename_param_k C, e_size_t N = 10 >
#else
template < typename_param_k I, typename_param_k C, e_size_t N >
#endif
struct sitos_impl
{
	static inline C const* convert(I num, C* buf, e_size_t const& n)
	{
		EXTL_MUST_BE_SIGNED(I);
		EXTL_ASSERT(NULL != buf);
		if(NULL == buf) return NULL;

		C* p = buf + n - 1;
		*p = 0;

		if((num < 0) && (N == 10)) /* Negative integer */
		{
			EXTL_ASSERT(n >= 3);
			if(n < 3)
			{
				buf[0] = static_cast<C>('\0');
				return buf;
			}

			do
			{
				I index = static_cast<I>(num % static_cast<I>(N));
				num = static_cast<I>(num / static_cast<I>(N));

				--p;

			#ifdef EXTL_COMPILER_IS_WATCOM
				*p = get_digit_char(static_cast<C*>(NULL))[index];
			#else
			#	ifdef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
				*p = get_digit_char<C>(static_cast<C*>(NULL))[index];
			#	else
				*p = get_digit_char<C>()[index];
			#	endif
			#endif
				
			}
			while (num != 0);
		
			*(--p) = C('-');

		}
		else /* Positive integer */
		{
			EXTL_ASSERT(n >= 2);
			if(n < 2)
			{
				buf[0] = static_cast<C>('\0');
				return buf;
			}

			do
			{
				I index = static_cast<I>(num % static_cast<I>(N));
				num = static_cast<I>(num / static_cast<I>(N));

				--p;

			#ifdef EXTL_COMPILER_IS_WATCOM
				*p = get_digit_char(static_cast<C*>(NULL))[index];
			#else
			#	ifdef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
				*p = get_digit_char<C>(static_cast<C*>(NULL))[index];
			#	else
				*p = get_digit_char<C>()[index];
			#	endif
			#endif

			}
			while (num != 0);
		}

		EXTL_ASSERT((p >= buf));
		
		return p;
	}

	static inline C const* convert(I num, C* buf, e_size_t const& n, e_size_t& result_count)
	{
		C const* p = convert(num, buf, n);
		result_count = n - (p - buf + 1);
		return p;
	}
};

/* ///////////////////////////////////////////////////////////////////////
 * itos<N>() implementation
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
/* //////////////////////////////////////////////////////////////////// */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
#	ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template < e_bool_t is_unsigned, e_bool_t is_signed, typename_param_k I, typename_param_k C, e_size_t N = 10 >
struct sign_selector;
#	else
template < e_bool_t is_unsigned, e_bool_t is_signed, typename_param_k I, typename_param_k C, e_size_t N >
struct sign_selector;
#	endif
#else
template < e_bool_t is_unsigned, e_bool_t is_signed >
struct sign_selector;
#endif

/* Select unsigned integer conversion */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
template < typename_param_k I, typename_param_k C, e_size_t N >
struct sign_selector< e_true_v, e_false_v, I, C, N >
{
#else
EXTL_TEMPLATE_SPECIALISATION
struct sign_selector< e_true_v, e_false_v >
{
#	ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	template < typename_param_k I, typename_param_k C, e_size_t N = 10 >
	struct itos_impl
	{
#	else
	template < typename_param_k I, typename_param_k C, e_size_t N >
	struct itos_impl
	{
#	endif
#endif
		static inline C const* convert(I num, C* buf, e_size_t const& n)
		{
			return uitos_impl<I, C, N>::convert(num, buf, n);
		}

		static inline C const* convert(I num, C* buf, e_size_t const& n, e_size_t& result_count)
		{
			C const* p = convert(num, buf, n);
			result_count = n - (p - buf + 1);
			return p;
		}

#ifndef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
	};
#endif
};

/* Select signed integer conversion */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
template < typename_param_k I, typename_param_k C, e_size_t N >
struct sign_selector< e_false_v, e_true_v, I, C, N >
{
#else
EXTL_TEMPLATE_SPECIALISATION
struct sign_selector< e_false_v, e_true_v >
{
#	ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	template < typename_param_k I, typename_param_k C, e_size_t N = 10 >
	struct itos_impl
	{
#	else
	template < typename_param_k I, typename_param_k C, e_size_t N >
	struct itos_impl
	{
#	endif
#endif
		static inline C const* convert(I num, C* buf, e_size_t const& n)
		{
			return sitos_impl<I, C, N>::convert(num, buf, n);
		}

		static inline C const* convert(I num, C* buf, e_size_t const& n, e_size_t& result_count)
		{
			C const* p = convert(num, buf, n);
			result_count = n - (p - buf + 1);
			return p;
		}

#ifndef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
	};
#endif
};
#endif /* EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST */
/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_END_NAMESPACE /* ::extl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */

#if defined(EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT)

/// uitos<N>() 
template < e_size_t N, typename_param_k I, typename_param_k C >
inline C const* uitos(I num, C* buf, e_size_t const& n)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C, N>::convert(num, buf, n);
}
/// uitos<N>() 
template < e_size_t N, typename_param_k I, typename_param_k C >
inline C const* uitos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C, N>::convert(num, buf, n, result_count);
}
/// sitos<N>() 
template < e_size_t N, typename_param_k I, typename_param_k C >
inline C const* sitos(I num, C* buf, e_size_t const& n)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C, N>::convert(num, buf, n);
}
/// sitos<N>() 
template < e_size_t N, typename_param_k I, typename_param_k C >
inline C const* sitos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C, N>::convert(num, buf, n, result_count);
}

/// itos<N>() 
template < e_size_t N, typename_param_k I, typename_param_k C >
inline C const* itos(I num, C* buf, e_size_t const& n)
{
#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
	return EXTL_NS_DETAIL(sign_selector)
		<
		(is_unsigned<I>::value),
		(is_signed<I>::value),
		I, C, N
		>::convert(num, buf, n);
#	else
    return EXTL_NS_DETAIL(sign_selector)
		<
		(is_unsigned<I>::value),
		(is_signed<I>::value)
		>::template_qual_k itos_impl<I, C, N>::convert(num, buf, n);
#	endif		
}
/// itos<N>() 
template < e_size_t N, typename_param_k I, typename_param_k C >
inline C const* itos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
	C const* p = itos<N, I, C>(num, buf, n);
	result_count = n - (p - buf + 1);
	return p;
}
/* ///////////////////////////////////////////////////////////////////////
 * Default: Decimal integer conversion
 */

/// uitos 
template < typename_param_k I, typename_param_k C >
inline C const* uitos(I num, C* buf, e_size_t const& n)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C>::convert(num, buf, n);
}
/// uitos 
template < typename_param_k I, typename_param_k C >
inline C const* uitos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C>::convert(num, buf, n, result_count);
}

/// sitos 
template < typename_param_k I, typename_param_k C >
inline C const* sitos(I num, C* buf, e_size_t const& n)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C>::convert(num, buf, n);
}
/// sitos 
template < typename_param_k I, typename_param_k C >
inline C const* sitos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C>::convert(num, buf, n, result_count);
}

/// itos 
template < typename_param_k I, typename_param_k C >
inline C const* itos(I num, C* buf, e_size_t const& n)
{
    return itos<10, I, C>(num, buf, n);
}
/// itos 
template < typename_param_k I, typename_param_k C >
inline C const* itos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
    return itos<10, I, C>(num, buf, n, result_count);
}
/* ///////////////////////////////////////////////////////////////////////
 * static array size determination 
 */
#ifdef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

/// utos 
template < e_size_t N, typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* uitos(I num, C (&buf)[BUF_COUNT])
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C, N>::convert(num, buf, BUF_COUNT);
}
/// utos 
template < e_size_t N, typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* uitos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C, N>::convert(num, buf, BUF_COUNT, result_count);
}
/// sitos 
template < e_size_t N, typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* sitos(I num, C (&buf)[BUF_COUNT])
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C, N>::convert(num, buf, BUF_COUNT);
}
/// sitos 
template < e_size_t N, typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* sitos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C, N>::convert(num, buf, BUF_COUNT, result_count);
}
/// itos 
template < e_size_t N, typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* itos(I num, C (&buf)[BUF_COUNT])
{
	return itos<N, I, C>(num, buf, BUF_COUNT);
}
/// itos 
template < e_size_t N, typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* itos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return itos<N, I, C>(num, buf, BUF_COUNT, result_count);
}
/* ///////////////////////////////////////////////////////////////////////
 * Default: Decimal integer conversion
 */

/// utos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* uitos(I num, C (&buf)[BUF_COUNT])
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C>::convert(num, buf, BUF_COUNT);
}
/// utos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* uitos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C>::convert(num, buf, BUF_COUNT, result_count);
}
/// sitos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* sitos(I num, C (&buf)[BUF_COUNT])
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C>::convert(num, buf, BUF_COUNT);
}
/// sitos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* sitos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C>::convert(num, buf, BUF_COUNT, result_count);
}
/// itos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* itos(I num, C (&buf)[BUF_COUNT])
{
	return itos<10, I, C>(num, buf, BUF_COUNT);
}
/// itos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* itos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return itos<10, I, C>(num, buf, BUF_COUNT, result_count);
}
#endif

#else /* !defined(EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT) */

/// uitos 
template < typename_param_k I, typename_param_k C >
inline C const* uitos(I num, C* buf, e_size_t const& n)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C, 10>::convert(num, buf, n);
}
/// uitos 
template < typename_param_k I, typename_param_k C >
inline C const* uitos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C, 10>::convert(num, buf, n, result_count);
}

/// sitos 
template < typename_param_k I, typename_param_k C >
inline C const* sitos(I num, C* buf, e_size_t const& n)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C, 10>::convert(num, buf, n);
}
/// sitos 
template < typename_param_k I, typename_param_k C >
inline C const* sitos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C, 10>::convert(num, buf, n, result_count);
}

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT)
/// itos 
template < typename_param_k I, typename_param_k C >
inline C const* itos(I num, C* buf, e_size_t const& n)
{
#	ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
	return EXTL_NS_DETAIL(sign_selector)
		<
		(is_unsigned<I>::value),
		(is_signed<I>::value),
		I, C, 10
		>::convert(num, buf, n);
#	else
    return EXTL_NS_DETAIL(sign_selector)
		<
		(is_unsigned<I>::value),
		(is_signed<I>::value)
		>::template_qual_k itos_impl<I, C, 10>::convert(num, buf, n);
#	endif		
}
/// itos 
template < typename_param_k I, typename_param_k C >
inline C const* itos(I num, C* buf, e_size_t const& n, e_size_t& result_count)
{
    C const* p = itos(num, buf, n);
	result_count = n - (p - buf + 1);
	return p;
}
#endif /* defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT) */

#	ifdef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
/// utos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* uitos(I num, C (&buf)[BUF_COUNT])
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C, 10>::convert(num, buf, BUF_COUNT);
}
/// utos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* uitos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return EXTL_NS_DETAIL(uitos_impl)<I, C, 10>::convert(num, buf, BUF_COUNT, result_count);
}
/// sitos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* sitos(I num, C (&buf)[BUF_COUNT])
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C, 10>::convert(num, buf, BUF_COUNT);
}
/// sitos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* sitos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return EXTL_NS_DETAIL(sitos_impl)<I, C, 10>::convert(num, buf, BUF_COUNT, result_count);
}

#		if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
			defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT)
/// itos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* itos(I num, C (&buf)[BUF_COUNT])
{
	return itos(num, buf, BUF_COUNT);
}
/// itos 
template < typename_param_k I, typename_param_k C, e_size_t BUF_COUNT >
inline C const* itos(I num, C (&buf)[BUF_COUNT], e_size_t& result_count)
{
	return itos(num, buf, BUF_COUNT, result_count);
}
#		endif /* defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
			defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT) */

#	endif /* EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */

#endif /* !defined(EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST) && \
		defined(EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT) */

/// i2s<> conversion shim
#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT)

#if defined(EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT)
#	ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template < typename_param_k C = e_tchar_t, e_size_t N = 10 > 
#	else
template < typename_param_k C, e_size_t N > 
#	endif
#else
template < typename_param_k C > 
#endif

class i2s
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	: public stack_buffer<C, EXTL_ITOS_MAX_CHAR_NUM>
#else
	: public stack_buffer	<	C
							,	EXTL_ITOS_MAX_CHAR_NUM
							,	typename_type_k memory_traits_selector<C>::memory_traits_type
							>
#endif
{
	private:
		
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		typedef stack_buffer<C, EXTL_ITOS_MAX_CHAR_NUM>			base_type;
	#else
		typedef stack_buffer<	C 
							,	EXTL_ITOS_MAX_CHAR_NUM 
							,	typename_type_k memory_traits_selector<C>::memory_traits_type
							>	base_type;
	#endif

	public:
	#if defined(EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT)
		typedef i2s<C, N>										class_type;
	#else
		typedef i2s<C>											class_type;
	#endif
		typedef typename_type_k base_type::size_type			size_type;
		typedef typename_type_k base_type::value_type			dest_type;
		typedef typename_type_k base_type::pointer				pointer;
		typedef typename_type_k base_type::const_pointer		const_pointer;
	
	private:
		size_type												m_result_count;

	public:
		template < typename_param_k I > 
		explicit_k i2s(I const& src)
		:	base_type(EXTL_ITOS_MAX_CHAR_NUM), /* 64 + 1 */
			m_result_count(0)
		{
			convert(src);
		}
	public:
		operator dest_type const*() const
		{
			const size_type n = base_type::size();
			const_pointer buf = base_type::data();

			return (buf + n - m_result_count - 1);
		}
	private:
		template < typename_param_k I > 
		void convert(I const& src)
		{
			const size_type n = base_type::size();
			const pointer buf = base_type::data();

		#if defined(EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT)
			itos<N, I, C>(src, buf, n, m_result_count);
		#else
			itos(src, buf, n, m_result_count);
		#endif
		}
};
#endif /* defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
			defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT) */

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_CONVERSION_ITOS_TEST_ENABLE
#	include "unit_test/itos_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONVERSION_ITOS_H */
/* //////////////////////////////////////////////////////////////////// */
