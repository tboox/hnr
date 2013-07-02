/* ///////////////////////////////////////////////////////////////////////
 * File:		system_traits_test.h		
 *
 * Created:		08.06.13				
 * Updated:		08.06.14
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_SYSTEM_TRAITS_TEST_H
#define EXTL_PLATFORM_WIN_SYSTEM_TRAITS_TEST_H

#ifndef EXTL_PLATFORM_WIN_SYSTEM_TRAITS_H
#	error This file must be included of system_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct system_traits_test
{
	system_traits_test()
	{
		EXTL_TEST_TRACE("/* //////////////////////////////////////////////////////////////////// */");
		EXTL_TEST_TRACE("system_traits Test:\n");

		e_tchar_t buffer[1 + EXTL_MAX_PATH];
		e_size_t size = system_traits<e_tchar_t>::get_current_filename(buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("size: %d, get_current_filename(): %s"), size, buffer);
		size = system_traits<e_tchar_t>::get_current_module_directory(buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("size: %d, get_current_module_directory(): %s"), size, buffer);
		size = system_traits<e_tchar_t>::get_system_directory(buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("size: %d, get_system_directory(): %s"), size, buffer);
		size = system_traits<e_tchar_t>::get_windows_directory(buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("size: %d, get_windows_directory(): %s"), size, buffer);
		size = system_traits<e_tchar_t>::get_environment_variable(_T("TEMP"), buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("size: %d, get_environment_variable() TEMP: %s"), size, buffer);
		size = system_traits<e_tchar_t>::expand_environment_strings(_T("%TEMP%"), buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("size: %d, expand_environment_strings() %%TEMP%%: %s"), size, buffer);
	}
};

system_traits_test g_system_traits_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_SYSTEM_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

