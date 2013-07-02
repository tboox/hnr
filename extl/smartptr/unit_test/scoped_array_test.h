/* ///////////////////////////////////////////////////////////////////////
 * File:		scoped_array_test.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SMART_PTR_SCOPED_ARRAY_TEST_H
#define EXTL_SMART_PTR_SCOPED_ARRAY_TEST_H

#ifndef EXTL_SMART_PTR_SCOPED_ARRAY_H
#	error This file must be included of scoped_array.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct scoped_array_test
{
	struct int_array_deleter
	{
		void operator()(int *p)
		{
			/*EXTL_ASSERT(0);*/
			delete[] p;
		}
	};

#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef scoped_array<int>											scoped_int_array;
#else
	typedef scoped_array<int, new_allocator<int>::array_deleter_type >	scoped_int_array;
#endif
	typedef scoped_array<int, int_array_deleter>						scoped_arrayArray;

	scoped_array_test()
	{
		scoped_int_array p1(new int[10]);
		p1[0] = 10;

		EXTL_ASSERT(p1);
		EXTL_ASSERT(p1 != NULL);
		EXTL_ASSERT(p1[0] == 10);

		{
			scoped_arrayArray p_array(new int[10]);
		}
	}
};
scoped_array_test g_scoped_array_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SMART_PTR_SCOPED_ARRAY_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

