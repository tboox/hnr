/* ///////////////////////////////////////////////////////////////////////
 * File:		test.h		
 *
 * Created:		08.11.24			
 * Updated:		08.11.24
 *
 * Brief:		The Container Library Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_TEST_H
#define EXTL_MATH_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../math.h"

#ifdef EXTL_MATH_VVECTOR_TEST_ENABLE
#	include "basic_vvector_test.h"
#endif

#ifdef EXTL_MATH_VMATRIX_TEST_ENABLE
#	include "basic_vmatrix_test.h"
#endif

#ifdef EXTL_MATH_EXPR_VVECTOR_SUPPORT
#	ifdef EXTL_MATH_VVECTOR_TEST_ENABLE
#		include "expr_vvector_test.h"
#	endif
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

