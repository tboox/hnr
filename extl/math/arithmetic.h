/* ///////////////////////////////////////////////////////////////////////
 * File:		arithmetic.h		
 *
 * Created:		08.12.19	
 * Updated:		08.12.19
 *
 * Brief:		The Arithmetic Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_ARITHMETIC_H
#define EXTL_MATH_ARITHMETIC_H

/*!\file arithmetic.h
 * \brief The Arithmetic Library
 */

#ifndef __cplusplus
#	error arithmetic.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "std/arithmetic.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

// exp(x)
EXTL_INLINE e_float_t xtl_exp(e_float_t x)
{
	return std_exp(x);
}
// sqrt(x)
EXTL_INLINE e_float_t xtl_sqrt(e_float_t x)
{
	return std_sqrt(x);
}
// sin(x)
EXTL_INLINE e_float_t xtl_sin(e_float_t x)
{
	return std_sin(x);
}
// cos(x)
EXTL_INLINE e_float_t xtl_cos(e_float_t x)
{
	return std_cos(x);
}

// ln(x)
EXTL_INLINE e_float_t xtl_ln(e_float_t x)
{
	return std_log(x);
}

// log10(x)
EXTL_INLINE e_float_t xtl_log10(e_float_t x)
{
	return xtl_ln(x) / EXTL_LN_10;
}

// lg(x) == log10(x)
EXTL_INLINE e_float_t xtl_lg(e_float_t x)
{
	return xtl_log10(x);
}

// log2(x)
EXTL_INLINE e_float_t xtl_log2(e_float_t x)
{
	return xtl_ln(x) / EXTL_LN_2;
}

// pow(p, x) = p^x
EXTL_INLINE e_float_t xtl_pow(e_float_t p, e_float_t x)
{
	return std_pow(p, x);
}

// pow2(p) = 2^x
EXTL_INLINE e_float_t xtl_pow2(e_float_t x)
{
	return std_pow(2, x);
}

/// round to the integer
EXTL_INLINE e_int_t xtl_round45(e_float_t x)
{
	return (x >= 0)? e_int_t(x + 0.5) : e_int_t(x - 0.5);
}

// xtl_abs(x) = |x|
template<typename_param_k Val> 
EXTL_INLINE Val xtl_abs(Val x)
{
	return ((x >= 0)? (x) : (-x));
}

// xtl_sgn(x)
template<typename_param_k Val> 
EXTL_INLINE Val xtl_sgn(Val x)
{
	return ((x > 0)? (1) : ((x < 0)? -1 : 0));
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_ARITHMETIC_H */
/* //////////////////////////////////////////////////////////////////// */
