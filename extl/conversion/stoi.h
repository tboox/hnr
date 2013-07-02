/* ///////////////////////////////////////////////////////////////////////
 * File:		stoi.h		
 *
 * Created:		08.03.14				
 * Updated:		08.05.09
 *
 * Brief: string  ==> integer
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONVERSION_STOI_H
#define EXTL_CONVERSION_STOI_H

/*!\file stoi.h
 * \brief string  ==> integer
 * 
 * - stoi<e_int_t, 10> 
 * - stoi<e_int_t>
 * - stoi ==> Default type: e_long_t
 * 
 * Compatibility:
 * - WATCOM: Only support stoi()
 * - VC6.0: Only support stoi()
 *
 */
#ifndef __cplusplus
#	error stoi.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */

#include "prefix.h"
#include "../type/traits/limit_traits.h"
#include "../type/traits/is_signed.h"
#include "../type/traits/is_unsigned.h"
#include "../error/error.h"

#ifdef EXTL_CONVERSION_STOI_TEST_ENABLE
#	include "../counter/counter.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* stoi<>() support */
#ifdef EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT
#	undef EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT
#endif

#if !defined(EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST) && \
			defined(EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT)
#	define EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT
#endif

/* correspond to i2s shim */
#define s2i	stoi

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Search Table 
 */

template < typename_param_k I >
#ifdef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST /* WATCOM */
inline I const* get_char_digit(I*)
#else
inline I const* get_char_digit()
#endif
{
    static I const s_digit_table[] =
    {
		  0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		, -1, -1, -1, -1, -1, -1, -1
		, 10, 11, 12, 13, 14, 15 /* 'A'-'F' */
		, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
		, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
		, -1, -1, -1, -1, -1, -1
		, 10, 11, 12, 13, 14, 15 /* 'a'-'f' */
    };

    return s_digit_table;
}

/* //////////////////////////////////////////////////////////////////// */
EXTL_DETAIL_BEGIN_NAMESPACE /* ::extl::detail namespace */
/* //////////////////////////////////////////////////////////////////// */

#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template < typename_param_k C, typename_param_k I = e_long_t, e_size_t N = 10 >
#else
template < typename_param_k C, typename_param_k I, e_size_t N >
#endif
struct stoi_impl
{
	public:
		typedef I	value_type;

	public:
		static inline I const convert(C const* buf)
		{
			C const* p = buf;
			I num = 0;

			EXTL_ASSERT(p != NULL);
			if(NULL == p) return num;

			if(*p == C('-')) /* signed integer */
			{
				EXTL_ASSERT((is_signed<I>::value));
				p++;
				while (*p != 0 && e_t_isdigit(*p))
				{
					num *= static_cast<I>(N);
					I index = static_cast<I>(*p) - static_cast<I>('0');
					
				#ifdef EXTL_COMPILER_IS_WATCOM
					num += get_char_digit(static_cast<I*>(NULL))[index];
				#else
				#	ifdef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
					num += get_char_digit<I>(static_cast<I*>(NULL))[index];
				#	else
					num += get_char_digit<I>()[index];
				#	endif
				#endif

					p++;
				}
				num *= static_cast<I>(-1);
			}
			else 
			{
				while (*p != 0 && e_t_isdigit(*p))
				{
					num *= static_cast<I>(N);
					I index = static_cast<I>(*p) - static_cast<I>('0');

				#ifdef EXTL_COMPILER_IS_WATCOM
					num += get_char_digit(static_cast<I*>(NULL))[index];
				#else
				#	ifdef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
					num += get_char_digit<I>(static_cast<I*>(NULL))[index];
				#	else
					num += get_char_digit<I>()[index];
				#	endif
				#endif

					p++;
				}
			}
			
			return num;
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE


/// Only support stoi() 
#if defined(EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST) || \
			!defined(EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT)
template < typename_param_k C >
inline e_long_t const stoi(C const* buf)
{
	return EXTL_NS_DETAIL(stoi_impl)<C, e_long_t, 10>::convert(buf);
}
#else /* support stoi<I,N>() */

	/* eg:
	 * template <typename T0, typename T1> void fun();
	 * template <typename T0> void fun();
	 * void fun();
	 * support overload
	 */
#	ifndef EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT
	/* VC6.0 does'nt support */
	/*template < typename_param_k I, e_size_t N, typename_param_k C >
	inline I const stoi(C const* buf)
	{
		return EXTL_NS_DETAIL(stoi_impl)<C, I, N>::convert(buf);
	}*/
#	else

/// support stoi<I,N>() 
template < typename_param_k I, e_size_t N, typename_param_k C >
inline I const stoi(C const* buf)
{
	return EXTL_NS_DETAIL(stoi_impl)<C, I, N>::convert(buf);
}
/// support stoi<I,N>() 
template < typename_param_k I, typename_param_k C >
inline I const stoi(C const* buf)
{
	return EXTL_NS_DETAIL(stoi_impl)<C, I>::convert(buf);
}
/// support stoi<I,N>() 
template < typename_param_k C >
inline typename_type_ret_k EXTL_NS_DETAIL(stoi_impl)<C>::
value_type const stoi(C const* buf)
{
	return EXTL_NS_DETAIL(stoi_impl)<C>::convert(buf);
}
#	endif /* EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT */
#endif /* EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST */


/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_CONVERSION_STOI_TEST_ENABLE
#	include "unit_test/stoi_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONVERSION_STOI_H */
/* //////////////////////////////////////////////////////////////////// */
