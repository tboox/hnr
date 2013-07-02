/* ///////////////////////////////////////////////////////////////////////
 * File:		address_of_test.h		
 *
 * Created:		08.04.01				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_ADDRESS_OF_TEST_H
#define EXTL_UTILITY_ADDRESS_OF_TEST_H

#ifndef EXTL_UTILITY_ADDRESS_OF_H
#	error This file must be included of address_of.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct address_of_test
{
	struct s
	{
		s():a(10){}
		int operator&(){return a;}
		int a;
	};
	address_of_test()
	{
		s sa;
		int aa = 5;
		int array[10];
		array[0] = 1;
		EXTL_ASSERT(EXTL_ADDRESS_OF(sa)->a == 10);
		EXTL_ASSERT(*EXTL_ADDRESS_OF(aa) == 5);
		EXTL_ASSERT(*EXTL_ADDRESS_OF(array)[0] == 1);

	}
};

address_of_test g_address_of_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_ADDRESS_OF_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
