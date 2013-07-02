/* ///////////////////////////////////////////////////////////////////////
 * File:		ebo_traits_test.h		
 *
 * Created:		08.03.31				
 * Updated:		08.04.16	
 *
 * Brief: EBO traits unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_COMPILER_TRAITS_EBO_TRAITS_TEST_H
#define EXTL_COMPILER_TRAITS_EBO_TRAITS_TEST_H

#ifndef EXTL_COMPILER_TRAITS_EBO_TRAITS_H
#	error This file must be included of ebo_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace 
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct ebo_traits_test
{
	ebo_traits_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("ebo_traits test:"));
		EXTL_TEST_TRACEA("current compiler: %s", EXTL_COMPILER_VERSION_STRING);
		EXTL_TEST_TRACE(_T("is_support_ebo1: %s"), ebo_traits::is_support_ebo1? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo2: %s"), ebo_traits::is_support_ebo2? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo3: %s"), ebo_traits::is_support_ebo3? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo4: %s"), ebo_traits::is_support_ebo4? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo5: %s"), ebo_traits::is_support_ebo5? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo6: %s"), ebo_traits::is_support_ebo6? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo7: %s\n"), ebo_traits::is_support_ebo7? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo: %s"), ebo_traits::is_support_ebo? _T("true") : _T("false"));
		EXTL_TEST_TRACE(_T("is_support_ebo_ex: %s\n"), ebo_traits::is_support_ebo_ex? _T("true") : _T("false"));
	}
};

ebo_traits_test g_ebo_traits_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace 
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_COMPILER_TRAITS_EBO_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
