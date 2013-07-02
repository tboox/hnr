/* ///////////////////////////////////////////////////////////////////////
 * File:		help_functions_test.h		
 *
 * Created:		08.03.10				
 * Updated:		08.04.14	
 *
 * Brief: Memory helpful functions unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_HELP_FUNCTIONS_TEST_H
#define EXTL_MEMORY_HELP_FUNCTIONS_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct help_functions_test
{
	help_functions_test()
	{
		//* WATCOM : Literal intergers need suffix u 
		e_char_t pbuf[100];
		EXTL_ASSERT(!pod_cmp_n(pod_copy_n(pbuf, "0123456789", 5u), "0123456789", 5u));
		EXTL_ASSERT(!non_pod_cmp_n(non_pod_copy_n(pbuf, "0123456789", 5u), "0123456789", 5u));

		EXTL_ASSERT(!pod_cmp_n(pod_fill_n(pbuf, 'a', 5u), "aaaaa", 5u));
		EXTL_ASSERT(!non_pod_cmp_n(non_pod_fill_n(pbuf, 'a', 5u), "aaaaa", 5u));

		EXTL_ASSERT(-1 == non_pod_cmp_n(non_pod_fill_n(pod_fill_0_n(pbuf, 5u), 'a', 3u), "aaaaa", 5u)); // aaa < aaaaa 
	
		e_wchar_t pwBuf[100];
		EXTL_ASSERT(!pod_cmp_n(pod_copy_n(pwBuf, L"0123456789", 5u), L"0123456789", 5u));
		EXTL_ASSERT(!non_pod_cmp_n(non_pod_copy_n(pwBuf, L"0123456789", 5u), L"0123456789", 5u));

		EXTL_ASSERT(!pod_cmp_n(pod_fill_n(pwBuf, L'a', 5u), L"aaaaa", 5u));
		EXTL_ASSERT(!non_pod_cmp_n(non_pod_fill_n(pwBuf, L'a', 5u), L"aaaaa", 5u));

		EXTL_ASSERT(-1 == non_pod_cmp_n(non_pod_fill_n(pod_fill_0_n(pwBuf, 5u), L'a', 3u), L"aaaaa", 5u)); // aaa < aaaaa 
	
	}
};

help_functions_test g_help_functions_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_HELP_FUNCTIONS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
