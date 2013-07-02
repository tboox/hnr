/* ///////////////////////////////////////////////////////////////////////
 * File:		pi_test.h		
 *
 * Created:		08.09.27		
 * Updated:		08.09.27
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_PI_TEST_H
#define EXTL_MPL_MATH_PI_TEST_H

#ifndef EXTL_MPL_MATH_PI_H
#	error This file must be included of pi.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct pi_test
{
	pi_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("pi<> Test:\n"));
		EXTL_TEST_TRACE(_T("%.4d"), pi<0>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<1>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<2>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<3>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<4>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<5>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<6>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<7>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<8>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<9>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<10>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<11>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<12>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<13>::value);
		EXTL_TEST_TRACE(_T("%.4d"), pi<14>::value);
		//pi<14>::make();
	}
};

pi_test g_pi_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_PI_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
