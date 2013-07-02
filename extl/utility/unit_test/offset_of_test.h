/* ///////////////////////////////////////////////////////////////////////
 * File:		offset_of_test.h		
 *
 * Created:		08.03.01				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_OFFSET_OF_TEST_H
#define EXTL_UTILITY_OFFSET_OF_TEST_H

#ifndef EXTL_UTILITY_OFFSET_OF_H
#	error This file must be included of offset_of.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct offset_of_test
{
	struct s
	{
		int a1;
		int a2;
	};
	offset_of_test()
	{
	#if defined(EXTL_COMPILER_IS_GCC) || \
			defined(EXTL_COMPILER_IS_WATCOM)

		EXTL_ASSERT((EXTL_OFFSET_OF(s,a1) == 0));
		EXTL_ASSERT((EXTL_OFFSET_OF(s,a2) == sizeof(int)));
	#else
		EXTL_STATIC_ASSERT((EXTL_OFFSET_OF(s,a1) == 0));
		EXTL_STATIC_ASSERT((EXTL_OFFSET_OF(s,a2) == sizeof(int)));
	#endif

	}
};

offset_of_test g_offset_of_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_OFFSET_OF_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
