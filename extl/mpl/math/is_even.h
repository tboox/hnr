/* ///////////////////////////////////////////////////////////////////////
 * File:		is_even.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief: is_even<N>
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_IS_EVEN_H
#define EXTL_MPL_MATH_IS_EVEN_H

/*!\file is_even.h
 * \brief is_even<N>
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "math.h"
#include "../int_.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_BEGIN_WHOLE_NAMESPACE 
/*!\brief: is_even class
 * 
 * \ingroup extl_group_mpl
 */
template < e_umax_int_t N >
struct is_even
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = ((N % 2) == 0));
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#ifdef EXTL_MPL_MATH_IS_EVEN_TEST_ENABLE
#	include "unit_test/is_even_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_IS_EVEN_H */
/* //////////////////////////////////////////////////////////////////// */
