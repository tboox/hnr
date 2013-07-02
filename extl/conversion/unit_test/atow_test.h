/* ///////////////////////////////////////////////////////////////////////
 * File:		atow_test.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONVERSION_ATOW_TEST_H
#define EXTL_CONVERSION_ATOW_TEST_H

#ifndef EXTL_CONVERSION_ATOW_H
#	error This file must be included of atow.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct atow_test
{
	atow_test()
	{
		e_char_t szCharBuf[100]="This is a ascii to unicode test. ";
		e_wchar_t szwCharBuf[100];

		EXTL_TEST_TRACE(_T("atow test:"));
		if(e_false_v == atow(szwCharBuf, szCharBuf, 100))
		{
			EXTL_TEST_TRACE(_T("atow failed"));
		};
		EXTL_TEST_TRACEW(L"atow result:%s", szwCharBuf);
		if(e_false_v == atow(szwCharBuf, szCharBuf))
		{
			EXTL_TEST_TRACE(_T("atow failed"));
		};
		EXTL_TEST_TRACEW(L"atow result:%s", szwCharBuf);

		EXTL_TEST_TRACE(_T("a2w result:"));
		EXTL_TEST_TRACEW(a2w(szCharBuf));

	}

};
atow_test g_atow_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONVERSION_ATOW_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

