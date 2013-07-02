/* ///////////////////////////////////////////////////////////////////////
 * File:		bit_field_test.h		
 *
 * Created:		08.10.02		
 * Updated:		08.10.02
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_BIT_FIELD_TEST_H
#define EXTL_CONTAINER_BIT_FIELD_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct bit_field_test
{
	bit_field_test()
	{
		bit_field<int> field1(2);
		EXTL_ASSERT(field1[0] == e_false_v);
		EXTL_ASSERT(field1[1] == e_false_v);

		bit_field<int> field2("10101002A0");

		/*field2.push_back(e_true_v);
		EXTL_ASSERT(field2.back() == e_true_v);
		EXTL_ASSERT(field2.size() == 11);
		field2.pop_back();

		EXTL_ASSERT(field2.front() == e_true_v);
		EXTL_ASSERT(field2.back() == e_false_v);
		EXTL_ASSERT(field2[0] == e_true_v);
		EXTL_ASSERT(field2[1] == e_false_v);*/
	
		field1.swap(field2);
		//EXTL_ASSERT(field2[0] == e_false_v);
		//EXTL_ASSERT(field2[1] == e_false_v);

		//EXTL_ASSERT(field1 != field2);

		e_size_t i;
		printf("\n constructor test:\n");
		for (i = 0; i < field1.size(); ++i)
		{
			printf("%d", field1[i]);
		}

		field1.resize(30);
		printf("\n resize(30) test:\n");
		for (i = 0; i < field1.size(); ++i)
		{
			printf("%d", field1[i]);
		}

		printf("\n iterator test:\n");
		for (bit_field<int>::const_iterator p = field1.begin(); p != field1.end(); ++p)
		{
			printf("%d", *p);
		}
		
		field1.reverse();
		printf("\n reverse test:\n");
		for (i = 0; i < field1.size(); ++i)
		{
			printf("%d", field1[i]);
		}

		printf("\n operator ~ test:\n");
		for (i = 0; i < (~field1).size(); ++i)
		{
			printf("%d", (~field1)[i]);
		}

		field1 = e_true_v;
		printf("\n assign(e_true_v) test:\n");
		for (i = 0; i < field1.size(); ++i)
		{
			printf("%d", field1[i]);
		}
	}
};

bit_field_test g_bit_field_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_BIT_FIELD_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

