/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_bit_field_test.h		
 *
 * Created:		08.10.02		
 * Updated:		08.10.02
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_FIXED_BIT_FIELD_TEST_H
#define EXTL_CONTAINER_FIXED_BIT_FIELD_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(fixed_bit_field_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int fixed_bit_field_test()
{
	fixed_bit_field<2, char> field1;
	EXTL_ASSERT(field1[0] == e_false_v);
	EXTL_ASSERT(field1[1] == e_false_v);

	fixed_bit_field<10, int> field2("10101002A0");

	EXTL_ASSERT(field2.front() == e_true_v);
	EXTL_ASSERT(field2.back() == e_false_v);
	EXTL_ASSERT(field2[0] == e_true_v);
	EXTL_ASSERT(field2[1] == e_false_v);

	e_size_t i;
	printf("\n constructor test:\n");
	for (i = 0; i < field2.size(); ++i)
	{
		printf("%d", field2[i]);
	}

	field2.reverse();
	printf("\n reverse test:\n");
	for (i = 0; i < field2.size(); ++i)
	{
		printf("%d", field2[i]);
	}

	printf("\n iterator test:\n");
	for (fixed_bit_field<10, int>::const_iterator p = field2.begin(); p != field2.end(); ++p)
	{
		printf("%d", *p);
	}

	printf("\n operator ~ test:\n");
	for (i = 0; i < (~field2).size(); ++i)
	{
		printf("%d", (~field2)[i]);
	}

	return 0;
}
int fixed_bit_field_test_ret = fixed_bit_field_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(fixed_bit_field_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_FIXED_BIT_FIELD_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

