/* ///////////////////////////////////////////////////////////////////////
 * File:		path_test.h		
 *
 * Created:		08.06.13				
 * Updated:		08.06.14
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_PATH_TEST_H
#define EXTL_PLATFORM_WIN_PATH_TEST_H

#ifndef EXTL_PLATFORM_WIN_PATH_H
#	error This file must be included of p.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct path_test
{
	struct foreach_test
	{
		void operator()(path::path_entry_type p)
		{
			EXTL_TEST_TRACE(_T("std_foreach test: pos:%d entry:%s"), p.pos(), p.name());
		}
	};
	path_test()
	{
		EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
		EXTL_TEST_TRACE(_T("path Test:\n"));

		path p(_T("C:\\dir\\file.txt"));
		EXTL_TEST_TRACE(_T("p.get_file_name(C:\\dir\\file.txt): %s"), p.get_file_name());
		EXTL_TEST_TRACE(_T("p.get_ext_name(C:\\dir\\file.txt): %s"), p.get_ext_name());
		EXTL_TEST_TRACE(_T("p.get_title_name(C:\\dir\\file.txt): %s\n"), p.get_title_name());

		p = _T("C:\\dir\\");
		EXTL_TEST_TRACE(_T("p.get_file_name(C:\\dir\\): %s"), p.get_file_name());
		EXTL_TEST_TRACE(_T("p.get_ext_name(C:\\dir\\): %s"), p.get_ext_name());
		EXTL_TEST_TRACE(_T("p.get_title_name(C:\\dir\\): %s\n"), p.get_title_name());

		p = _T("C:\\dir");
		EXTL_TEST_TRACE(_T("p.get_file_name(C:\\dir): %s"), p.get_file_name());
		EXTL_TEST_TRACE(_T("p.get_ext_name(C:\\dir): %s"), p.get_ext_name());
		EXTL_TEST_TRACE(_T("p.get_title_name(C:\\dir): %s\n"), p.get_title_name());

		p.pop();
		EXTL_TEST_TRACE(_T("C:\\dir => p.pop(): %s"), p.c_str());
		p.push(_T("dir"));
		EXTL_TEST_TRACE(_T("C:\\ => p.push(dir): %s\n"), p.c_str());

		p.push_ext_name(_T("txt"));
		EXTL_TEST_TRACE(_T("C:\\ => p.push_ext_name(txt): %s"), p.c_str());
		p.pop_ext_name();
		EXTL_TEST_TRACE(_T("C:\\ => p.pop_ext_name(): %s\n"), p.c_str());

		p.pop(e_false_v);
		EXTL_TEST_TRACE(_T("C:\\dir => p.pop(e_false_v): %s"), p.c_str());
		p.push(_T("dir"), e_true_v);
		EXTL_TEST_TRACE(_T("C:\\ => p.push(dir, e_true_v): %s\n"), p.c_str());

		p /= _T("dir");
		EXTL_TEST_TRACE(_T("C:\\ => p /= dir: %s"), p.c_str());

		p.push(p);
		EXTL_TEST_TRACE(_T("C:\\ => p.push(p): %s\n"), p.c_str());

		EXTL_ASSERT(_T("C:\\dir\\dir") == p);
		EXTL_ASSERT(_T("C:\\dir\\dir\\") != p);

		p = p / p;
		EXTL_ASSERT(_T("C:\\dir\\dir") == p);

		p = p / _T("dir");
		EXTL_ASSERT(_T("C:\\dir\\dir\\dir") == p);

		EXTL_TEST_TRACE(_T("\nentry_const_iterator test:"));
		p = _T("C:\\dir\\file.txt"); 
		for (path::const_entry_iterator i = p.entry_begin(); i != p.entry_end(); ++i)
		{
			EXTL_TEST_TRACE(_T("path:%s pos:%d entry:%s"), p.c_str(), i->pos(), i->name());
		}

		EXTL_TEST_TRACE(_T("\nentry_const_reverse_iterator test:"));
		p = _T("C:\\dir\\file.txt"); 
		for (path::const_reverse_entry_iterator ri = p.entry_rbegin(); ri != p.entry_rend(); ++ri)
		{
			EXTL_TEST_TRACE(_T("path:%s pos:%d entry:%s"), p.c_str(), ri->pos(), ri->name());
		}
		std_foreach(p.entry_begin(), p.entry_end(), foreach_test());
		std_foreach(p.entry_rbegin(), p.entry_rend(), foreach_test());

		EXTL_TEST_TRACE(_T("\nmake_relative_path: %s"), p.make_relative_path().c_str());
		EXTL_TEST_TRACE(_T("make_absolute_path: %s"), p.make_absolute_path().c_str());
		EXTL_TEST_TRACE(_T("make_current_directory: %s"), p.make_current_directory().c_str());

	}
};

path_test g_path_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_PATH_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

