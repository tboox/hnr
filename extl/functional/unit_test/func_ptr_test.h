/* ///////////////////////////////////////////////////////////////////////
 * File:		func_ptr_test.h		
 *
 * Created:		08.06.11		
 * Updated:		08.06.11	
 *
 * Brief: func_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_FUNCTIONAL_FUNC_PTR_TEST_H
#define EXTL_FUNCTIONAL_FUNC_PTR_TEST_H

#ifndef EXTL_FUNCTIONAL_FUNC_PTR_H
#	error This file must be included of func_ptr_test.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

struct func_ptr_test
{
	static void func(e_tchar_t const* str)
	{
		EXTL_TEST_TRACE(str);
	}
	func_ptr_test()
	{
		EXTL_TEST_TRACE(_T("func_ptr_test:"));

		typedef func_ptr<void (*)(e_tchar_t const*)>	func_ptr_type;

		func_ptr_type fp(&func);
		log_base< e_tchar_t, func_ptr_type ,EXTL_LOG_RECORD_MAX_SIZE> log(fp);
		log.report(_T("run func"));
	}
};

func_ptr_test g_func_ptr_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_FUNCTIONAL_FUNC_PTR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

