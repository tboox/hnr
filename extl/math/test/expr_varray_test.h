/* ///////////////////////////////////////////////////////////////////////
 * File:		expr_varray_test.h		
 *
 * Created:		08.08.14			
 * Updated:		08.08.14
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MATH_EXPR_VARRAY_TEST_H
#define EXTL_MATH_EXPR_VARRAY_TEST_H

#ifndef EXTL_MATH_EXPR_VARRAY_H
#	error This file must be included of expr_varray.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(expr_varray_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct expr_varray_test
{
	expr_varray_test()
	{
		typedef buffer_selector<int>::buffer_type	buffer_type;
		typedef basic_varray<int, buffer_type>		array_type;

		array_type ar(1, 1000);
		array_type ar2(1, 1000);

		expr_varray<int, array_type > par(ar);
		expr_varray<int, array_type > par2(ar2);

		/*clock_counter t;
		int volatile i;

		EXTL_TEST_TRACE(_T("//////////////////////////////////////////////////////////////////////////"));
		EXTL_TEST_TRACE(_T("expr_varray Test:\n"));

		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			ar2 = ar + ar + ar + ar;
		}
		t.end();
		EXTL_TEST_TRACE(_T("basic_varray: %d"), t.ms());

		// Slowly now, need optimization
		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			par2 = par + par + par + par;
		}

		t.end();
		EXTL_TEST_TRACE(_T("expr_varray: %d\n"), t.ms());

		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			int volatile a = (ar + ar + ar + ar)[0];
		}
		t.end();
		EXTL_TEST_TRACE(_T("(ar + ar + ar + ar)[0]: %d"), t.ms());

		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			int volatile a = ar[0] + ar[0] + ar[0] + ar[0];
		}
		t.end();
		EXTL_TEST_TRACE(_T("ar[0] + ar[0] + ar[0] + ar[0]: %d"), t.ms());

		t.begin();
		for (i = 0; i < 10000; ++i)
		{
			int volatile a = (par + par + par + par)[0];
		}

		t.end();
		EXTL_TEST_TRACE(_T("(par + par + par + par)[0]: %d\n"), t.ms());*/

		par2 = par + par + par - par;
		EXTL_ASSERT(ar2[10] == 2);

	#ifdef EXTL_MATH_EOP_SCALAR_SUPPORT
		par2 = par + par + par - par * 5;
		EXTL_ASSERT(ar2[10] == -2);
	#endif
	}
};

expr_varray_test g_expr_varray_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(expr_varray_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_EXPR_VARRAY_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

