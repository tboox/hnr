/* ///////////////////////////////////////////////////////////////////////
 * File:		compiler_traits_test.h		
 *
 * Created:		08.03.31				
 * Updated:		08.04.16	
 *
 * Brief: Compiler traits unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_COMPILER_TRAITS_TEST_H
#define EXTL_COMPILER_TRAITS_TEST_H

#ifndef EXTL_COMPILER_TRAITS_H
#	error This file must be included of compiler_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace 
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct compiler_traits_test
{
	compiler_traits_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("compiler_traits test:"));
		EXTL_TEST_TRACEA("current compiler: %s", EXTL_COMPILER_VERSION_STRING);
		
		/* EBO */
		EXTL_TEST_TRACE(_T("is_support_ebo: %s"), compiler_traits::is_support_ebo? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo_ex: %s\n"), compiler_traits::is_support_ebo_ex? _T("true") : _T("false"));
		
		/* EDO */
		EXTL_TEST_TRACE(_T("is_support_edo: %s"), compiler_traits::is_support_edo? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo_ex: %s\n"), compiler_traits::is_support_edo_ex? _T("true") : _T("false"));
	
		/* RVO */
		EXTL_TEST_TRACE(_T("is_support_rvo: %s"), compiler_traits::is_support_rvo()? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_nrvo: %s"), compiler_traits::is_support_nrvo()? _T("true") : _T("false"));
	}
};

compiler_traits_test g_compiler_traits_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace 
 */
EXTL_TEST_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_COMPILER_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

