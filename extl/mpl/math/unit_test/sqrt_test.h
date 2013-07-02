/* ///////////////////////////////////////////////////////////////////////
 * File:		sqrt_test.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.09
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_SQRT_TEST_H
#define EXTL_MPL_MATH_SQRT_TEST_H

#ifndef EXTL_MPL_MATH_SQRT_H
#	error This file must be included of sqrt.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void sqrt_test()
{
	EXTL_STATIC_ASSERT((sqrt<5>::value == 2));
	EXTL_STATIC_ASSERT((sqrt<16>::value == 4));
	EXTL_STATIC_ASSERT((sqrt<64>::value == 8));
}

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_SQRT_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
