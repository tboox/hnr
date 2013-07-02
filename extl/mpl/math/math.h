/* ///////////////////////////////////////////////////////////////////////
 * File:		math.h		
 *
 * Created:		08.03.17				
 * Updated:		08.11.20
 *
 * Brief:		The Math Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MPL_MATH_H
#define EXTL_MPL_MATH_H

#ifndef __cplusplus
#	error math.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "is_even.h"
#include "is_prime.h"

#ifdef EXTL_MPL_MATH_LOG_SUPPORT
#	include "log.h"
#endif

#ifdef EXTL_MPL_MATH_PI_SUPPORT
#	include "pi.h"
#endif

#ifdef EXTL_MPL_MATH_POW_SUPPORT
#	include "pow.h"
#endif

#ifdef EXTL_MPL_MATH_SQRT_SUPPORT
#	include "sqrt.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_H */
/* //////////////////////////////////////////////////////////////////// */

