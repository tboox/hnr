/* ///////////////////////////////////////////////////////////////////////
 * File:		wtoa_test.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONVERSION_WTOA_TEST_H
#define EXTL_CONVERSION_WTOA_TEST_H

#ifndef EXTL_CONVERSION_WTOA_H
#	error This file must be included of wtoa.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct wtoa_test
{
	wtoa_test()
	{
		e_wchar_t szwCharBuf[100]=L"This is a unicode to ascii test. ";
		e_char_t szCharBuf[100];

		EXTL_TEST_TRACE(_T("wtoa test:"));
		if(e_false_v == wtoa(szCharBuf, szwCharBuf, 100))
		{
			EXTL_TEST_TRACE(_T("wtoa failed"));
		};
		EXTL_TEST_TRACEA("wtoa result:%s", szCharBuf);
		if(e_false_v == wtoa(szCharBuf, szwCharBuf))
		{
			EXTL_TEST_TRACE(_T("wtoa failed"));
		};
		EXTL_TEST_TRACEA("wtoa result:%s", szCharBuf);

		EXTL_TEST_TRACE(_T("w2a result:"));
		EXTL_TEST_TRACEA(w2a(szwCharBuf));

	}

};
wtoa_test g_wtoa_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONVERSION_WTOA_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

