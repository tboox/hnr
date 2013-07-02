/* ///////////////////////////////////////////////////////////////////////
 * File:		path_traits_test.h		
 *
 * Created:		08.06.13				
 * Updated:		08.06.14
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_PATH_TRAITS_TEST_H
#define EXTL_PLATFORM_WIN_PATH_TRAITS_TEST_H

#ifndef EXTL_PLATFORM_WIN_PATH_TRAITS_H
#	error This file must be included of path_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct path_traits_test
{
	path_traits_test()
	{
		EXTL_TEST_TRACE("/* //////////////////////////////////////////////////////////////////// */");
		EXTL_TEST_TRACE("path_traits Test:\n");

		e_tchar_t dir[1 + EXTL_MAX_PATH] = _T("C:\\file");

		path_traits<e_tchar_t>::push_sep(dir);
		EXTL_TEST_TRACE(_T("push_sep(C:\\file): %s"), dir);
		path_traits<e_tchar_t>::pop_sep(dir);
		EXTL_TEST_TRACE(_T("pop_sep(C:\\file\\): %s\n"), dir);

		path_traits<e_tchar_t>::push(dir, _T("file2"));
		EXTL_TEST_TRACE(_T("push(file2): %s"), dir);
		path_traits<e_tchar_t>::pop(dir);
		EXTL_TEST_TRACE(_T("pop(): %s\n"), dir);

		path_traits<e_tchar_t>::push_ext_name(dir, _T("txt"));
		EXTL_TEST_TRACE(_T("push_ext_name(txt): %s"), dir);
		path_traits<e_tchar_t>::pop_ext_name(dir);
		EXTL_TEST_TRACE(_T("pop_ext_name(): %s\n"), dir);

		EXTL_TEST_TRACE(_T("path entry enum: C:\\dir1\\/.\\..\\dir2\\.\\dir3/dir4\\\\file.txt"));
		typedef path_traits<e_tchar_t>::path_entry_type path_entry_type;
		path_entry_type ei(path_entry_type::en_enum_all);
		if (path_traits<e_tchar_t>::entry_enum_start(_T("C:\\dir1\\/.\\..\\dir2\\.\\dir3/dir4\\\\file.txt"), ei))
		{
			do
			{
				EXTL_TEST_TRACE(_T("name:%s"), ei.name());
			}
			while (path_traits<e_tchar_t>::entry_enum(ei));

			path_traits<e_tchar_t>::entry_enum_stop(ei);
		}

		EXTL_TEST_TRACE(_T("\npattern_all : %s"), path_traits<e_tchar_t>::pattern_all());
	}
};

path_traits_test g_path_traits_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_PATH_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

