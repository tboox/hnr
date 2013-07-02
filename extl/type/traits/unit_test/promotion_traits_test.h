/* ///////////////////////////////////////////////////////////////////////
 * File:		promotion_traits_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: promotion_traits unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_H
#	error This file must be included of promotion_traits_test.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void promotion_traits_test()
{
	typedef promotion_traits<void, void>::type	promotion_traits_test_type1;
	EXTL_MUST_BE_VOID(promotion_traits_test_type1);

	/*typedef promotion_traits<void, int>::type	promotion_traits_test_type2;
	EXTL_MUST_BE_VOID(promotion_traits_test_type2);*/

	typedef promotion_traits<int, float>::type	promotion_traits_test_type3;
	EXTL_MUST_BE_FLOAT(promotion_traits_test_type3);

	typedef promotion_traits<char, double>::type	promotion_traits_test_type4;
	EXTL_MUST_BE_FLOAT(promotion_traits_test_type4);

	typedef promotion_traits<int, char>::type	promotion_traits_test_type5;
	EXTL_MUST_BE_INT(promotion_traits_test_type5);

	typedef promotion_traits<int, int>::type	promotion_traits_test_type6;
	EXTL_MUST_BE_INT(promotion_traits_test_type6);

	
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
