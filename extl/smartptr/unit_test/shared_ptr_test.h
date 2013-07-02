/* ///////////////////////////////////////////////////////////////////////
 * File:		shared_ptr_test.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SMART_PTR_SHARED_PTR_TEST_H
#define EXTL_SMART_PTR_SHARED_PTR_TEST_H

#ifndef EXTL_SMART_PTR_SHARED_PTR_H
#	error This file must be included of shared_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct shared_ptr_test
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
	typedef shared_ptr<int>													shared_int_ptr;
	typedef shared_ptr<void>												shared_void_ptr;
#else
	typedef shared_ptr<int, new_allocator<int>::object_deleter_type >		shared_int_ptr;
	typedef shared_ptr<void, new_allocator<void>::object_deleter_type >		shared_void_ptr;
#endif
	typedef shared_ptr<int, int_array_deleter>								shared_array_ptr;

	shared_ptr_test()
	{
		shared_int_ptr p1(new int(10));

		EXTL_ASSERT(p1.count() == 1);

		{
			shared_int_ptr p2(p1);
			EXTL_ASSERT(p1.count() == 2);
			EXTL_ASSERT(p2.count() == 2);

		}
		EXTL_ASSERT(p1.is_unique());

		EXTL_ASSERT(*p1 == 10);

		p4 = p1;
		EXTL_ASSERT(p4.count() == 2);
		EXTL_ASSERT(p1.count() == 2);
		EXTL_ASSERT(*p4 == 10);

		p1 = p4;
		EXTL_ASSERT(p4.count() == 2);
		EXTL_ASSERT(p1.count() == 2);

	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		{
			shared_void_ptr p5(p1);
			p5.reset(new int);
		}
	#endif
		EXTL_ASSERT(p1 == p4);

		shared_int_ptr p7(new int(10));
		EXTL_ASSERT(p7.count() == 1);
		shared_int_ptr p8(p7);
		EXTL_ASSERT(p7.count() == 2);
		p8.reset(new int(10));
		EXTL_ASSERT(p7.count() == 1);
		EXTL_ASSERT(p8.count() == 1);

		EXTL_ASSERT(p1 != NULL);
		EXTL_ASSERT(p1);
		EXTL_ASSERT(p1 && 1);
		EXTL_ASSERT(p1 == p4);
		EXTL_ASSERT(p1 != p7);

		{
			shared_array_ptr p9(new int[10]);
			*p9 = 10;
			EXTL_ASSERT(*p9 == 10);
		}
	}

	shared_int_ptr p4;
};

shared_ptr_test g_shared_ptr_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SMART_PTR_SHARED_PTR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

