/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_hash_test.h		
 *
 * Created:		08.08.25			
 * Updated:		08.08.25
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_FIXED_HASH_TEST_H
#define EXTL_CONTAINER_FIXED_HASH_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(fixed_hash_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int fixed_hash_test()
{
#if defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT) && \
		!defined(EXTL_COMPILER_IS_DMC)
	typedef fixed_hash<e_char_t const*, int>					hash_type;
#else
	typedef fixed_hash	<	e_char_t const*
						,	int
						,	EXTL_FIXED_HASH_DEFAULT_TABLE_SIZE
						,	hash_key_traits<e_char_t const*, EXTL_FIXED_HASH_DEFAULT_TABLE_SIZE>
						,	allocator_selector<int>::allocator_type
						>										hash_type;
#endif

	hash_type h1, h2;
	EXTL_ASSERT(h1.size() == 0);

	h1["key_1"] = 1; 
	EXTL_ASSERT(h1.size() == 1);
	EXTL_ASSERT(h1["key_1"] == 1);

	h1["key_1"] = 2; 
	EXTL_ASSERT(h1.size() == 1);
	EXTL_ASSERT(h1["key_1"] == 2);

	h1.insert("key_1", 3);
	EXTL_ASSERT(h1.size() == 2);
	EXTL_ASSERT(h1.count("key_1") == 2);

	h1.erase("key_1");
	EXTL_ASSERT(h1.count("key_1") == 0);
	EXTL_ASSERT(h1.size() == 0);

	h1["key_1"] = 1;
	h1["key_2"] = 2;
	h1["key_3"] = 3;
	h1["key_4"] = 4;
	h1["key_5"] = 5;

	fixed_hash<int, double> a;
	for (int i = 0; i < 10; i++) a[5] = 5;
	for (fixed_hash<int, double>::const_iterator d = a.begin(); d != a.end(); ++d) printf("key: %d, value: %f\n", (*d).first(), (*d).second());

	h2.swap(h1);
	for (hash_type::const_iterator p = h2.begin(); p != h2.end(); ++p)
	{
		printf("key: %s, value: %d\n", (*p).first(), (*p).second());
	}

	h2.erase("key_1");
	EXTL_ASSERT(h2.size() == 4);
	EXTL_ASSERT(h2.count("key_2") == 1);

	h2.clear();
	EXTL_ASSERT(h2.size() == 0);

	e_size_t hv = hash_type::hash_value("key_1");
	for (hash_type::const_local_iterator lp = h2.begin(hv); lp != h2.end(hv); ++lp)
	{
		printf("key: %s, value: %d\n", (*lp).first(), (*lp).second());
	}
	return 0;
}

int fixed_hash_test_ret = fixed_hash_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_list_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_FIXED_HASH_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

