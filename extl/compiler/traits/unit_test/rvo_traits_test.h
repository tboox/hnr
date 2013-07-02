/* ///////////////////////////////////////////////////////////////////////
 * File:		rvo_traits_test.h		
 *
 * Created:		08.03.31				
 * Updated:		08.04.16	
 *
 * Brief: RVO traits unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_COMPILER_TRAITS_RVO_TRAITS_TEST_H
#define EXTL_COMPILER_TRAITS_RVO_TRAITS_TEST_H

#ifndef EXTL_COMPILER_TRAITS_RVO_TRAITS_H
#	error This file must be included of rvo_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace 
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct rvo_traits_test
{
	rvo_traits_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("rvo_traits test:"));
		EXTL_TEST_TRACEA("current compiler: %s", EXTL_COMPILER_VERSION_STRING);
		EXTL_TEST_TRACE(_T("is_support_rvo: %s\n"), rvo_traits::is_support_rvo()? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_nrvo: %s\n"), rvo_traits::is_support_nrvo()? _T("true") : _T("false"));
	}
};

rvo_traits_test g_rvo_traits_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace 
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_COMPILER_TRAITS_RVO_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

