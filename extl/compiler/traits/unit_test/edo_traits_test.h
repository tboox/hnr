/* ///////////////////////////////////////////////////////////////////////
 * File:		edo_traits_test.h		
 *
 * Created:		08.03.20			
 * Updated:		08.04.16	
 *
 * Brief: EDO traits unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_COMPILER_TRAITS_EDO_TRAITS_TEST_H
#define EXTL_COMPILER_TRAITS_EDO_TRAITS_TEST_H

#ifndef EXTL_COMPILER_TRAITS_EDO_TRAITS_H
#	error This file must be included of edo_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace 
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct edo_traits_test
{
	edo_traits_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("edo_traits test:"));
		EXTL_TEST_TRACEA("current compiler: %s", EXTL_COMPILER_VERSION_STRING);
		EXTL_TEST_TRACE(_T("is_support_edo1: %s"), edo_traits::is_support_edo1? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo2: %s"), edo_traits::is_support_edo2? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo3: %s"), edo_traits::is_support_edo3? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo4: %s"), edo_traits::is_support_edo4? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo5: %s"), edo_traits::is_support_edo5? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo6: %s"), edo_traits::is_support_edo6? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo7: %s"), edo_traits::is_support_edo7? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo8: %s\n"), edo_traits::is_support_edo8? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo: %s"), edo_traits::is_support_edo? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_edo_ex: %s\n"), edo_traits::is_support_edo_ex? _T("true") : _T("false"));
	}
};

edo_traits_test g_edo_traits_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace 
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_COMPILER_TRAITS_EDO_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

