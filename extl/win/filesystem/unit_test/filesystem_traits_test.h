/* ///////////////////////////////////////////////////////////////////////
 * File:		filesystem_traits_test.h		
 *
 * Created:		08.06.13				
 * Updated:		08.06.14
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_FILESYSTEM_TRAITS_TEST_H
#define EXTL_PLATFORM_WIN_FILESYSTEM_TRAITS_TEST_H

#ifndef EXTL_PLATFORM_WIN_FILESYSTEM_TRAITS_H
#	error This file must be included of filesystem_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct filesystem_traits_test
{
	filesystem_traits_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("filesystem_traits Test:\n"));
		
		// file_enum test
		EXTL_TEST_TRACE(_T("file_enum Test:"));
		filesystem_traits<e_tchar_t>::file_entry_type fi;
		if (filesystem_traits<e_tchar_t>::file_enum_start(_T("C:\\Documents and Settings\\*.*"), fi))
		{
			do
			{
				EXTL_TEST_TRACE(_T("%s"), fi.filename());
			}
			while (filesystem_traits<e_tchar_t>::file_enum(fi));

			filesystem_traits<e_tchar_t>::file_enum_stop(fi);
		}
		// get_current_directory test
		EXTL_TEST_TRACE(_T("\n"));
		e_tchar_t buffer[EXTL_MAX_PATH];
		filesystem_traits<e_tchar_t>::get_current_directory(buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("get_current_directory(): %s"), buffer);

		// drives test
		EXTL_TEST_TRACE(_T("drive exists A: %s"), filesystem_traits<e_tchar_t>::drive_exists(_T('A'))? _T("yes") : _T("no"));
		EXTL_TEST_TRACE(_T("drive exists B: %s"), filesystem_traits<e_tchar_t>::drive_exists(_T('B'))? _T("yes") : _T("no"));		
		EXTL_TEST_TRACE(_T("drive exists C: %s"), filesystem_traits<e_tchar_t>::drive_exists(_T('C'))? _T("yes") : _T("no"));
		EXTL_TEST_TRACE(_T("drive exists D: %s"), filesystem_traits<e_tchar_t>::drive_exists(_T('D'))? _T("yes") : _T("no"));	
		EXTL_TEST_TRACE(_T("drive exists E: %s"), filesystem_traits<e_tchar_t>::drive_exists(_T('E'))? _T("yes") : _T("no"));
		EXTL_TEST_TRACE(_T("drive exists F: %s\n"), filesystem_traits<e_tchar_t>::drive_exists(_T('F'))? _T("yes") : _T("no"));

		EXTL_TEST_TRACE(_T("is_drive_removable A: %s"), filesystem_traits<e_tchar_t>::is_drive_removable(_T('A'))? _T("yes") : _T("no"));
		EXTL_TEST_TRACE(_T("is_drive_fixed C: %s"), filesystem_traits<e_tchar_t>::is_drive_fixed(_T('C'))? _T("yes") : _T("no"));
		EXTL_TEST_TRACE(_T("is_drive_fixed D: %s"), filesystem_traits<e_tchar_t>::is_drive_fixed(_T('D'))? _T("yes") : _T("no"));	
		EXTL_TEST_TRACE(_T("is_drive_fixed E: %s"), filesystem_traits<e_tchar_t>::is_drive_fixed(_T('E'))? _T("yes") : _T("no"));
		EXTL_TEST_TRACE(_T("is_drive_cdrom G: %s\n"), filesystem_traits<e_tchar_t>::is_drive_cdrom(_T('G'))? _T("yes") : _T("no"));
		
		EXTL_ASSERT(filesystem_traits<e_tchar_t>::create_directory(_T("test")));

		// get_absolute_path & get_relative_path test
		e_tchar_t buffer2[EXTL_MAX_PATH];
		EXTL_TEST_TRACE(_T("get_absolute_path & get_relative_path test"));
		filesystem_traits<e_tchar_t>::get_absolute_path(_T("."), buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T(". ==> %s"), buffer);
		filesystem_traits<e_tchar_t>::get_relative_path(buffer, buffer2, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("%s ==> %s\n"), buffer, buffer2);

		filesystem_traits<e_tchar_t>::get_absolute_path(_T(".."), buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T(".. ==> %s"), buffer);
		filesystem_traits<e_tchar_t>::get_relative_path(buffer, buffer2, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("%s ==> %s\n"), buffer, buffer2);

		filesystem_traits<e_tchar_t>::get_absolute_path(_T("test"), buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("test ==> %s"), buffer);
		filesystem_traits<e_tchar_t>::get_relative_path(buffer, buffer2, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("%s ==> %s\n"), buffer, buffer2);

		filesystem_traits<e_tchar_t>::get_absolute_path(_T("..\\..\\test"), buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("..\\..\\test ==> %s"), buffer);
		filesystem_traits<e_tchar_t>::get_relative_path(buffer, buffer2, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("%s ==> %s\n"), buffer, buffer2);

		filesystem_traits<e_tchar_t>::get_absolute_path(_T("dir1\\dir2\\..\\test"), buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("dir1\\dir2\\..\\test ==> %s"), buffer);
		filesystem_traits<e_tchar_t>::get_relative_path(buffer, buffer2, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("%s ==> %s\n"), buffer, buffer2);

		filesystem_traits<e_tchar_t>::get_absolute_path(_T("C:\\test"), buffer, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("C:\\test ==> %s"), buffer);
		filesystem_traits<e_tchar_t>::get_relative_path(_T("..\\test"), buffer2, EXTL_MAX_PATH);
		EXTL_TEST_TRACE(_T("..\\test ==> %s\n"), buffer2);
		
		EXTL_ASSERT(filesystem_traits<e_tchar_t>::remove_directory(_T("test")));
	}
};

filesystem_traits_test g_filesystem_traits_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_FILESYSTEM_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

