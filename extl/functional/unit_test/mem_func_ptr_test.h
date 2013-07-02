/* ///////////////////////////////////////////////////////////////////////
 * File:		mem_func_ptr_test.h		
 *
 * Created:		08.06.11		
 * Updated:		08.06.11	
 *
 * Brief: mem_func_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_FUNCTIONAL_MEM_FUNC_PTR_TEST_H
#define EXTL_FUNCTIONAL_MEM_FUNC_PTR_TEST_H

#ifndef EXTL_FUNCTIONAL_MEM_FUNC_PTR_H
#	error This file must be included of mem_func_ptr_test.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

struct mem_func_ptr_test
{
	void func(e_tchar_t const* str)
	{
		EXTL_TEST_TRACE(str);
	}
	mem_func_ptr_test()
	{
		EXTL_TEST_TRACE(_T("mem_func_ptr_test:"));
		typedef mem_func_ptr<void (mem_func_ptr_test::*)(e_tchar_t const*)>	mem_func_ptr_type;

		mem_func_ptr_type fp(this, &mem_func_ptr_test::func);
		log_base< e_tchar_t, mem_func_ptr_type ,EXTL_LOG_RECORD_MAX_SIZE> log(fp);
		log.report(_T("run func"));
	}
};

mem_func_ptr_test g_mem_func_ptr_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_FUNCTIONAL_MEM_FUNC_PTR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

