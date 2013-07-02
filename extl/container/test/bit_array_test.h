/* ///////////////////////////////////////////////////////////////////////
 * File:		bit_array_test.h		
 *
 * Created:		08.10.02		
 * Updated:		08.10.02
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_BIT_ARRAY_TEST_H
#define EXTL_CONTAINER_BIT_ARRAY_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(bit_array_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int bit_array_test()
{
	typedef bit_array<char, buffer_selector<char>::buffer_type>				bit_array_type;
	
	bit_array_type array1(2);
	EXTL_ASSERT(array1[0] == e_false_v);
	EXTL_ASSERT(array1[1] == e_false_v);

	bit_array_type array2("10101002A0");

	array2.push_back(e_true_v);
	EXTL_ASSERT(array2.back() == e_true_v);
	EXTL_ASSERT(array2.size() == 11);
	array2.pop_back();

	EXTL_ASSERT(array2.front() == e_true_v);
	EXTL_ASSERT(array2.back() == e_false_v);
	EXTL_ASSERT(array2[0] == e_true_v);
	EXTL_ASSERT(array2[1] == e_false_v);

	array1.swap(array2);
	EXTL_ASSERT(array2[0] == e_false_v);
	EXTL_ASSERT(array2[1] == e_false_v);

	
	EXTL_ASSERT(array1 != array2);
	array2 = array1;
	EXTL_ASSERT(array1 == array2);

	e_size_t i;
	printf("\n constructor test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	printf("\n iterator test:\n");
	for (bit_array_type::const_iterator p = array1.begin(); p != array1.end(); ++p)
	{
		printf("%d", *p);
	}

	printf("\n operator ~ test:\n");
	for (i = 0; i < (~array1).size(); ++i)
	{
		printf("%d", (~array1)[i]);
	}

	array1 += e_true_v;
	printf("\n operator += e_true_v test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1 += "10101002A0";
	printf("\n operator += 10101002A0 test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1.clean();
	printf("\n clean test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1.replace(1, 1, "10101");
	printf("\n replace test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1.replace(1, 5, e_true_v, 5);
	printf("\n replace test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1.replace(1, 5, e_false_v);
	printf("\n replace test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1.insert(1, "10101");
	printf("\n insert test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1.reverse();
	printf("\n reverse test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1.reverse();
	printf("\n reverse test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	array1.erase(1, 5);
	printf("\n erase test:\n");
	for (i = 0; i < array1.size(); ++i)
	{
		printf("%d", array1[i]);
	}

	return 0;
}
int bit_array_test_ret = bit_array_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(bit_array_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_BIT_ARRAY_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

