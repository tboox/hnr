/* ///////////////////////////////////////////////////////////////////////
 * File:		pi.h		
 *
 * Created:		08.09.27				
 * Updated:		08.09.27
 *
 * Brief: Caculate pi = 3.14159265358979
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_PI_H
#define EXTL_MPL_MATH_PI_H

/*!\file pi.h
 * \brief Caculate pi = 3.14159265358979
 *
 */
#ifndef EXTL_MPL_MATH_PI_SUPPORT
#	error extl::pi is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "math.h"
#include "pow.h"
#include "../int_.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_PI_TRAITS_MAX_BITCOUNT	(15)
#define EXTL_PI_TRAITS_MAX_BITWIDTH	(1)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_BEGIN_WHOLE_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifdef EXTL_MPL_SUPPORT

/*!\brief: pi class
 * 
 * \param N bit count of pi
 *
 * \ingroup extl_group_mpl
 *
 * formula:\n
 * <pre>
 *           1          2          3                      k
 * pi = 2 + --- * (2 + --- * (2 + --- * (2 + ...  (2 + ------- * (2 + ... ))...)))
 *           3          5          7                    2k + 1
 *
 * </pre>
 *
 * algorithm:\n
 * \code
	int count = 2800, error = 0, error_array[2801] = {0}; 
	int deta_value = 2000 * 10000; 
	while (count != 0)
	{ 
		int value = 0; 
		for (int i = count; i > 0; i--)
		{
			int next = value + error_array[i] * 10000;
			error_array[i] = next % (2 * i + 1);
			value = (next / (2 * i + 1)) * i + deta_value;
		} 
		count = count - 14; 
		printf("%.4d", error + value / 10000); 
		error = value % 10000; 

		deta_value = 0;
	} 
 * \endcode
 */
template<e_umax_int_t N>
struct pi
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, count = pi<N - 1>::count - 14						);
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, base = pow_10<EXTL_PI_TRAITS_MAX_BITWIDTH>::value	);

	template<e_umax_int_t I>
	struct pi_impl
	{
		#if defined(EXTL_COMPILER_IS_INTEL)
			typedef pi<N - 1>::template_qual_k pi_impl<I>	prev_pi_impl;
			EXTL_STATIC_MEMBER_CONST(e_umax_int_t, next = pi_impl<I + 1>::value + base * (prev_pi_impl::error) );
		#else
			EXTL_STATIC_MEMBER_CONST(e_umax_int_t, next = pi_impl<I + 1>::value + base * (pi<N - 1>::template_qual_k pi_impl<I>::error) );
		#endif

		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = (next / (2 * I + 1)) * I	);
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, error = (next % (2 * I + 1))		);
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct pi_impl<count>
	{
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = 0 );
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, error = 0 );
	};

	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = pi<N - 1>::error + pi_impl<1>::value / base	);
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, error = pi_impl<1>::value % base						);

	~pi()
	{
		EXTL_STATIC_ASSERT(EXTL_PI_TRAITS_MAX_BITWIDTH < 5);
	}

	/*static void make()
	{
		pi<N - 1>::make();
		printf("%.1d", value);
	}*/
};

EXTL_TEMPLATE_SPECIALISATION
struct pi<0>
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, count = (14 * (EXTL_PI_TRAITS_MAX_BITCOUNT + 1))		);
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, base = pow_10<EXTL_PI_TRAITS_MAX_BITWIDTH>::value	);

	template<e_umax_int_t I>
	struct pi_impl
	{
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, next = pi_impl<I + 1>::value						);
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = ((next) / (2 * I + 1)) * I + 2 * base	);
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, error = (next % (2 * I + 1))						);
	};

	EXTL_TEMPLATE_SPECIALISATION
	struct pi_impl<count>
	{
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = 2 * base	);
		EXTL_STATIC_MEMBER_CONST(e_umax_int_t, error = 0		);
	};

	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = pi_impl<1>::value / base );
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, error = pi_impl<1>::value % base );

	~pi()
	{
		EXTL_STATIC_ASSERT(EXTL_PI_TRAITS_MAX_BITWIDTH < 5);
	}

	/*static void make()
	{
		printf("%.1d.", value);
	}*/
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#if defined(EXTL_MPL_MATH_PI_TEST_ENABLE) && \
		defined(EXTL_MPL_MATH_PI_SUPPORT)
#	include "unit_test/pi_test.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_SUPPORT */
/* //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_PI_H */
/* //////////////////////////////////////////////////////////////////// */
