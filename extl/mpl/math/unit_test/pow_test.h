/* ///////////////////////////////////////////////////////////////////////
 * File:		pow_test.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.09
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_POW_TEST_H
#define EXTL_MPL_MATH_POW_TEST_H

#ifndef EXTL_MPL_MATH_POW_H
#	error This file must be included of pow.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void pow_test()
{
	EXTL_STATIC_ASSERT((pow<2, 10>::value == 1024));
	EXTL_STATIC_ASSERT((pow<3, 3>::value == 27));
	EXTL_STATIC_ASSERT((pow<3, 0>::value == 1));
	EXTL_STATIC_ASSERT((pow<3, 1>::value == 3));

	EXTL_STATIC_ASSERT((pow_2<10>::value == 1024));
	EXTL_STATIC_ASSERT((pow_10<2>::value == 100));
}

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_POW_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
