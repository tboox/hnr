/* ///////////////////////////////////////////////////////////////////////
 * File:		scoped_ptr_test.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SMART_PTR_SCOPED_PTR_TEST_H
#define EXTL_SMART_PTR_SCOPED_PTR_TEST_H

#ifndef EXTL_SMART_PTR_SCOPED_PTR_H
#	error This file must be included of scoped_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct scoped_ptr_test
{
	struct int_array_deleter
	{
		void operator()(int *p)
		{
			/*EXTL_ASSERT(0);*/
			if(NULL != p) delete[] p;
		}
	};

#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef scoped_ptr<int>													scoped_int_ptr;
	typedef scoped_ptr<void>												scoped_void_ptr;
#else
	typedef scoped_ptr<int, new_allocator<int>::object_deleter_type >		scoped_int_ptr;
	typedef scoped_ptr<void, new_allocator<void>::object_deleter_type >		scoped_void_ptr;
#endif
	typedef scoped_ptr<int, int_array_deleter>								scoped_array_ptr;

	scoped_ptr_test()
	{
		scoped_int_ptr p1(new int(10));
	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		{
			scoped_void_ptr p2(new int(10));
		}
	#endif

		EXTL_ASSERT(p1);
		EXTL_ASSERT(p1 != NULL);

		{
			scoped_array_ptr pArray(new int[10]);
		}
	}
};

scoped_ptr_test g_scoped_ptr_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SMART_PTR_SCOPED_PTR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

