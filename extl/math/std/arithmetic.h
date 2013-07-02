/* ///////////////////////////////////////////////////////////////////////
 * File:		arithmetic.h		
 *
 * Created:		08.11.23		
 * Updated:		08.11.23	
 *
 * Brief:		The Std-Arithmetic Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_STD_ARITHMETIC_H
#define EXTL_MATH_STD_ARITHMETIC_H

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
#include <math.h>

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

// exp(x)
EXTL_INLINE e_float_t std_exp(e_float_t x)
{
	return exp(x);
}
// sqrt(x)
EXTL_INLINE e_float_t std_sqrt(e_float_t x)
{
	return sqrt(x);
}
// sin(x)
EXTL_INLINE e_float_t std_sin(e_float_t x)
{
	return sin(x);
}
// cos(x)
EXTL_INLINE e_float_t std_cos(e_float_t x)
{
	return cos(x);
}
// log(x) = ln(x)
EXTL_INLINE e_float_t std_log(e_float_t x)
{
	return log(x);
}
// pow(p, x) = p^x
EXTL_INLINE e_float_t std_pow(e_float_t p, e_float_t x)
{
	return pow(p, x);
}

// abs(x) = |x|
EXTL_INLINE e_int_t std_abs(e_int_t x)
{
	return abs(x);
}

// fabs(x) = |x|
EXTL_INLINE e_float_t std_fabs(e_float_t x)
{
	return fabs(x);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_STD_ARITHMETIC_H */
/* //////////////////////////////////////////////////////////////////// */
