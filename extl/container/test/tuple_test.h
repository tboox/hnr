/* ///////////////////////////////////////////////////////////////////////
 * File:		tuple_test.h		
 *
 * Created:		08.07.23			
 * Updated:		08.07.23
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_TUPLE_TEST_H
#define EXTL_CONTAINER_TUPLE_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(tuple_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct tuple_test
{
	tuple_test()
	{
	#if EXTL_WORKAROUND_MSVC(==, 1200)
		tuple<int, char*, int> t(1, "123", 10);

		EXTL_ASSERT(get_tuple_element<0>(t) == 1);
		set_tuple_element<0>(t, 2);
		EXTL_ASSERT(get_tuple_element<0>(t) == 2);
		set_tuple_element<0>(t, 15);
		EXTL_ASSERT(get_tuple_element<0>(t) == 15);
		EXTL_STATIC_ASSERT(2 == (tuple_elements_size<tuple<int, int> >::value));
		EXTL_ASSERT(t.size() == 3);

		tuple<int, char*, int> t2(10, "456", 232);

		t.swap(t2);
		EXTL_ASSERT(get_tuple_element<0>(t2) == 15);
		EXTL_ASSERT(get_tuple_element<0>(t) == 10);

		EXTL_ASSERT(get_tuple_element<2>(t2) == 10);
		EXTL_ASSERT(get_tuple_element<2>(t) == 232);

		swap(t, t2);
		EXTL_ASSERT(get_tuple_element<0>(t2) == 10);
		EXTL_ASSERT(get_tuple_element<0>(t) == 15);

		EXTL_ASSERT(get_tuple_element<2>(t2) == 232);
		EXTL_ASSERT(get_tuple_element<2>(t) == 10);

	#else
		tuple<int, void*, int> t(1, NULL, 1);
		EXTL_ASSERT(get_tuple_element<0>(t) == 1);
		set_tuple_element<0>(t, 2);
		EXTL_ASSERT(get_tuple_element<0>(t) == 2);
		t.set<0>(15);
		EXTL_ASSERT(t.get<0>() == 15);
		EXTL_STATIC_ASSERT(2 == (tuple_elements_size<tuple<int, int> >::value));
		EXTL_ASSERT(t.size() == 3);
		EXTL_ASSERT(t.get<1>() == NULL);

		tuple<int, void*, int> t2(10, NULL, 232);
		t.swap(t2);
		EXTL_ASSERT(t2.get<0>() == 15);
		EXTL_ASSERT(t.get<0>() == 10);

		EXTL_ASSERT(t2.get<2>() == 1);
		EXTL_ASSERT(t.get<2>() == 232);

		swap(t, t2);
		EXTL_ASSERT(t2.get<0>() == 10);
		EXTL_ASSERT(t.get<0>() == 15);

		EXTL_ASSERT(t2.get<2>() == 232);
		EXTL_ASSERT(t.get<2>() == 1);
	#endif

		EXTL_TEST_TRACE(_T("sizeof(tuple<>) test:"));
		EXTL_TEST_TRACE(_T("sizeof(tuple<int, tuple_test>): %d\n"), sizeof(tuple<int, tuple_test>));
		EXTL_TEST_TRACE(_T("sizeof(tupletuple<int, double, char, int>): %d\n"), sizeof(tuple<int, double, char, int>));
	}
};

tuple_test g_tuple_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(tuple_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_TUPLE_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

