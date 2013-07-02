/* ///////////////////////////////////////////////////////////////////////
 * File:		expr_vvector_test.h		
 *
 * Created:		08.08.14			
 * Updated:		09.01.27
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MATH_EXPR_VVECTOR_TEST_H
#define EXTL_MATH_EXPR_VVECTOR_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(expr_vvector_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct expr_vvector_test
{
	expr_vvector_test()
	{
		typedef buffer_selector<int>::buffer_type	buffer_type;
		typedef basic_vvector<int, buffer_type>		vvector_type;

		vvector_type vv(1, 1000);
		vvector_type vv2(1, 1000);

		expr_vvector<int, vvector_type > pvv(vv);
		expr_vvector<int, vvector_type > pvv2(vv2);

		/*clock_counter t;
		int volatile i;

		EXTL_TEST_TRACE(_T("//////////////////////////////////////////////////////////////////////////"));
		EXTL_TEST_TRACE(_T("expr_vvector Test:\n"));

		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			vv2 = vv + vv + vv + vv;
		}
		t.end();
		EXTL_TEST_TRACE(_T("basic_vvector: %d"), t.ms());

		// Slowly now, need optimization
		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			pvv2 = pvv + pvv + pvv + pvv;
		}

		t.end();
		EXTL_TEST_TRACE(_T("expr_vvector: %d\n"), t.ms());

		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			int volatile a = (vv + vv + vv + vv)[0];
		}
		t.end();
		EXTL_TEST_TRACE(_T("(vv + vv + vv + vv)[0]: %d"), t.ms());

		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			int volatile a = vv[0] + vv[0] + vv[0] + vv[0];
		}
		t.end();
		EXTL_TEST_TRACE(_T("vv[0] + vv[0] + vv[0] + vv[0]: %d"), t.ms());

		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			int volatile a = (pvv + pvv + pvv + pvv)[0];
		}

		t.end();
		EXTL_TEST_TRACE(_T("(pvv + pvv + pvv + pvv)[0]: %d\n"), t.ms());*/

		pvv2 = pvv + pvv + pvv - pvv;
		EXTL_ASSERT(vv2[10] == 2);

	#ifdef EXTL_MATH_EOP_SCALAR_SUPPORT
		pvv2 = pvv + pvv + pvv - pvv * 5;
		EXTL_ASSERT(vv2[10] == -2);
	#endif
	}
};

expr_vvector_test g_expr_vvector_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(expr_vvector_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_EXPR_VVECTOR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

