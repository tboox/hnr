/* ///////////////////////////////////////////////////////////////////////
 * File:		factorial_test.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.09
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_FACTORIAL_TEST_H
#define EXTL_MPL_MATH_FACTORIAL_TEST_H

#ifndef EXTL_MPL_MATH_FACTORIAL_H
#	error This file must be included of factorial.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void factorial_test()
{
	EXTL_STATIC_ASSERT((factorial<0>::value == 1));
	EXTL_STATIC_ASSERT((factorial<1>::value == 1));
	EXTL_STATIC_ASSERT((factorial<2>::value == 2));
	EXTL_STATIC_ASSERT((factorial<3>::value == 6));
	EXTL_STATIC_ASSERT((factorial<4>::value == 24));
	EXTL_STATIC_ASSERT((factorial<5>::value == 120));
}

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_FACTORIAL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
