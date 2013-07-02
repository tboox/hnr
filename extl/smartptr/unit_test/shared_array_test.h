/* ///////////////////////////////////////////////////////////////////////
 * File:		shared_array_test.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SMART_PTR_SHARED_ARRAY_TEST_H
#define EXTL_SMART_PTR_SHARED_ARRAY_TEST_H

#ifndef EXTL_SMART_PTR_SHARED_ARRAY_H
#	error This file must be included of shared_array.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* DMC Bug: The following code will be not compiled successfully if there is not the statement */
#ifdef EXTL_COMPILER_IS_DMC
shared_array<int> bug;
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct shared_array_test
{
	struct int_array_deleter
	{
		void operator()(int *p)
		{
			/* EXTL_ASSERT(0); */
			if(NULL != p) delete[] p;
		}
	};

#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef shared_array<int>											shared_int_array;
#else
	typedef shared_array<int, new_allocator<int>::array_deleter_type >	shared_int_array;
#endif
	typedef shared_array<int, int_array_deleter>						shared_array_array;

	shared_array_test()
	{
		shared_int_array p1(new int[10]);
		p1[0] = 10;

		EXTL_ASSERT(p1.count() == 1);

		{
			shared_int_array p2(p1);
			EXTL_ASSERT(p1.count() == 2);
			EXTL_ASSERT(p2.count() == 2);

		}
		EXTL_ASSERT(p1.is_unique());

		EXTL_ASSERT(p1[0] == 10);
		EXTL_ASSERT(p1);
		EXTL_ASSERT(p1 != NULL);

		p4 = p1;
		EXTL_ASSERT(p4.count() == 2);
		EXTL_ASSERT(p1.count() == 2);
		EXTL_ASSERT(p4[0] == 10);

		p1 = p4;
		EXTL_ASSERT(p4.count() == 2);
		EXTL_ASSERT(p1.count() == 2);

		EXTL_ASSERT(p1 == p4);
	}

	shared_int_array p4;
};
shared_array_test g_shared_array_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SMART_PTR_SHARED_ARRAY_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

