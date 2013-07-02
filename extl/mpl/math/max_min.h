/* ///////////////////////////////////////////////////////////////////////
 * File:		max_min.h		
 *
 * Created:		08.05.13				
 * Updated:		08.05.13
 *
 * Brief: The maximum and minimum value
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_MAX_MIN_H
#define EXTL_MPL_MATH_MAX_MIN_H

/*!\file max_min.h
 * \brief The maximum and minimum value
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

/// The maximum value 
template < e_umax_int_t N1, e_umax_int_t N2 >
struct max
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = (N1 > N2)? N1 : N2);
};

/// The maximum value 
template < e_umax_int_t N1, e_umax_int_t N2 >
struct max_2 : max<N1, N2> {};

/// The maximum value 
template < e_umax_int_t N1, e_umax_int_t N2, e_umax_int_t N3 >
struct max_3
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = ((max<N1, N2>::value) > N3)? (max<N1, N2>::value) : N3);
};

/// The maximum value 
template < e_umax_int_t N1, e_umax_int_t N2, e_umax_int_t N3, e_umax_int_t N4 >
struct max_4
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = ((max<N1, N2>::value) > (max<N3, N4>::value))? 
													(max<N1, N2>::value) : (max<N3, N4>::value));
};

/// The minimum value 
template < e_umax_int_t N1, e_umax_int_t N2 >
struct min
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = (N1 < N2)? N1 : N2);
};

/// The minimum value 
template < e_umax_int_t N1, e_umax_int_t N2 >
struct min_2 : min<N1, N2> {};

/// The minimum value 
template < e_umax_int_t N1, e_umax_int_t N2, e_umax_int_t N3 >
struct min_3
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = ((min<N1, N2>::value) < N3)? (min<N1, N2>::value) : N3);
};

/// The minimum value 
template < e_umax_int_t N1, e_umax_int_t N2, e_umax_int_t N3, e_umax_int_t N4 >
struct min_4
{
	EXTL_STATIC_MEMBER_CONST(e_umax_int_t, value = ((min<N1, N2>::value) < (min<N3, N4>::value))? 
													(min<N1, N2>::value) : (min<N3, N4>::value));
};
/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */
#ifdef EXTL_MPL_MATH_MAX_MIN_TEST_ENABLE
#	include "unit_test/max_min_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_MAX_MIN_H */
/* //////////////////////////////////////////////////////////////////// */
