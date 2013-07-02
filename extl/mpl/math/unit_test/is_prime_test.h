/* ///////////////////////////////////////////////////////////////////////
 * File:		is_prime_test.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.09
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_IS_PRIME_TEST_H
#define EXTL_MPL_MATH_IS_PRIME_TEST_H

#ifndef EXTL_MPL_MATH_IS_PRIME_H
#	error This file must be included of is_prime.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_prime_test()
{
	EXTL_STATIC_ASSERT((is_prime<2>::value));
	EXTL_STATIC_ASSERT((is_prime<3>::value));
	EXTL_STATIC_ASSERT((is_prime<7>::value));
	EXTL_STATIC_ASSERT((is_prime<11>::value));
	EXTL_STATIC_ASSERT((is_prime<13>::value));
	EXTL_STATIC_ASSERT((is_prime<17>::value));
	EXTL_STATIC_ASSERT((is_prime<19>::value));

	EXTL_STATIC_ASSERT(!(is_prime<16>::value));
	EXTL_STATIC_ASSERT(!(is_prime<64>::value));
	EXTL_STATIC_ASSERT(!(is_prime<0>::value));
	EXTL_STATIC_ASSERT(!(is_prime<1>::value));
	EXTL_STATIC_ASSERT(!(is_prime<100>::value));
}

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_IS_PRIME_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
