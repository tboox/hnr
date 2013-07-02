/* ///////////////////////////////////////////////////////////////////////
 * File:		object_counter_test.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_OBJECT_COUNTER_TEST_H
#define EXTL_OBJECT_COUNTER_TEST_H

#ifndef EXTL_OBJECT_COUNTER_H
#	error This file must be included of object_counter.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct object_counter_test 
{
	struct obj : public object_counter<obj>
	{
	};
	object_counter_test()
	{
		{
			obj a;
			EXTL_ASSERT(object_counter<obj>::get_object_count() == 1);
			obj b(a);
			EXTL_ASSERT(object_counter<obj>::get_object_count() == 2);
			EXTL_ASSERT(object_counter<obj>::get_copy_count() == 1);
		}
		EXTL_ASSERT(object_counter<obj>::get_object_count() == 0);

	}
};

object_counter_test g_object_counter_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_OBJECT_COUNTER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
