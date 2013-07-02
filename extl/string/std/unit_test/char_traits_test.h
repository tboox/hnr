/* ///////////////////////////////////////////////////////////////////////
 * File:		std_char_traits_test.h		
 *
 * Created:		08.03.20					
 * Updated:		08.04.14	
 *
 * Brief: std_char_traits unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_STD_CHAR_TRAITS_TEST_H
#define EXTL_STRING_STD_CHAR_TRAITS_TEST_H

#ifndef EXTL_STRING_STD_CHAR_TRAITS_H
#	error This file must be included of std_char_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct std_char_traits_test
{
	std_char_traits_test()
	{
		EXTL_ASSERT(std_char_traits<e_tchar_t>::eq(_T('A'), _T('A')));

		e_tchar_t s[100] = _T("Char copy Test");
		e_int_t len = std_char_traits<e_tchar_t>::length(s);
		e_tchar_t str[100];
		EXTL_ASSERT(!std_char_traits<e_tchar_t>::compare(std_char_traits<e_tchar_t>::copy(str, s ,len), s, 10)); /* == */
		EXTL_ASSERT(-1 == std_char_traits<e_tchar_t>::compare(std_char_traits<e_tchar_t>::copy(str, s ,len), s, 10)); /* < */

		EXTL_ASSERT(!std_char_traits<e_tchar_t>::compare(std_char_traits<e_tchar_t>::assign(str, _T('a'), 10), _T("aaaaaaaaaa"), std_char_traits<e_tchar_t>::length(_T("aaaaaaaaaa")))); /* == */
	}
};

std_char_traits_test g_std_char_traits_test;

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_STD_CHAR_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

