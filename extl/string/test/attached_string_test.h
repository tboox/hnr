/* ///////////////////////////////////////////////////////////////////////
 * File:		attached_string_test.h		
 *
 * Created:		08.06.14					
 * Updated:		08.06.14	
 *
 * Brief: attached_string unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_ATTACHED_STRING_TEST_H
#define EXTL_STRING_ATTACHED_STRING_TEST_H

#ifndef EXTL_STRING_ATTACHED_STRING_H
#	error This file must be included of attached_string.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(attached_string_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int attached_string_test()
{
	typedef attached_string char_attached_string;
	e_tchar_t b1[] = _T("123456789");
	e_tchar_t b2[] = _T("123456789");
	e_tchar_t b3[] = _T("987654321");

	char_attached_string char_string1;
	char_attached_string char_string2;
	char_attached_string char_string3;

	char_string1.attach(b1);
	char_string2.attach(b2);
	char_string3.attach(b3);

	EXTL_ASSERT(char_string1 == char_string2);
	EXTL_ASSERT(char_string1 != char_string3);

	EXTL_ASSERT(char_string1 < char_string3);
	EXTL_ASSERT(char_string3 > char_string1);
	EXTL_ASSERT(char_string1 <= char_string3);
	EXTL_ASSERT(char_string3 >= char_string1);

	EXTL_ASSERT(_T("123456789") == char_string2);
	EXTL_ASSERT(_T("123456789") != char_string3);

	EXTL_ASSERT(char_string1 == _T("123456789"));
	EXTL_ASSERT(char_string1 != _T("987654321"));

	EXTL_ASSERT(char_string1 < _T("987654321"));
	EXTL_ASSERT(char_string3 > _T("123456789"));
	EXTL_ASSERT(char_string1 <= _T("987654321"));
	EXTL_ASSERT(char_string3 >= _T("123456789"));

	EXTL_ASSERT(_T("123456789") < char_string3);
	EXTL_ASSERT(_T("987654321") > char_string1);
	EXTL_ASSERT(_T("123456789") <= char_string3);
	EXTL_ASSERT(_T("987654321") >= char_string1);

	// replace operation 
	e_tchar_t b4[EXTL_STRING_ATTACHED_STRING_MAX_SPACE];
	char_attached_string char_string4(b4);

	char_string4 = _T("12345");
	char_string4.replace(0, 1, _T("aaa"), 3);

	EXTL_ASSERT(!char_string4.compare(_T("aaa2345")));

	char_string4.replace(7, 0, _T("aaa"), 3);
	EXTL_ASSERT(!char_string4.compare(_T("aaa2345aaa")));

	char_string4.replace(0, 3, char_string4.c_str() + 3, 4);
	EXTL_ASSERT(!char_string4.compare(_T("23452345aaa")));

	char_string4.replace(0, 4, char_string4.c_str() + 8, 3);
	EXTL_ASSERT(!char_string4.compare(_T("aaa2345aaa")));

	char_string4.replace(7, 3, char_string4.c_str(), 7);
	EXTL_ASSERT(!char_string4.compare(_T("aaa2345aaa2345")));

	char_string4.replace(3, 4, char_string4.c_str() + 5, 9);
	EXTL_ASSERT(!char_string4.compare(_T("aaa45aaa2345aaa2345")));

	char_string4.replace(8, 4, char_string4.c_str() + 5, 14);
	EXTL_ASSERT(!char_string4.compare(_T("aaa45aaaaaa2345aaa2345aaa2345")));


	char_string4 = _T("12345");

	char_string4.replace(0, 1, _T("aaa"));
	EXTL_ASSERT(!char_string4.compare(_T("aaa2345")));

	char_string4.replace(char_string4.begin(), char_string4.end(), char_string4);
	EXTL_ASSERT(!char_string4.compare(_T("aaa2345")));

	char_string4.replace(char_string4.begin(), char_string4.end(), _T('a'));
	EXTL_ASSERT(!char_string4.compare(_T("a")));

	char_string4.replace(char_string4.begin(), _T('a'), 2);
	EXTL_ASSERT(!char_string4.compare(_T("aa")));

	char_string4.replace(char_string4.begin(), char_string4.end(), char_string4.begin(), char_string4.end());
	EXTL_ASSERT(!char_string4.compare(_T("aa")));

	// find string 
	char_string4 = _T("12345aa12345");
	EXTL_ASSERT(5 == char_string4.find(_T("aa")));
	EXTL_ASSERT(char_string4.fof() == char_string4.find(_T("aa4545")));
	EXTL_ASSERT(5 == char_string4.find(_T('a')));

	// rfind string 
	char_string4 = _T("12345aa12345");
	EXTL_ASSERT(7 == char_string4.rfind(_T("12345")));
	EXTL_ASSERT(char_string4.fof() == char_string4.rfind(_T("123dsad45aa")));
	EXTL_ASSERT(6 == char_string4.rfind(_T('a')));

	// replace string in the whole context 
	char_string4 = _T("12345aa1234512345");
	char_string4.replace_all(_T("12345"), _T("1"));
	EXTL_ASSERT(!char_string4.compare(_T("1aa11")));
	char_string4.replace_all(_T('a'), _T('b'));
	EXTL_ASSERT(!char_string4.compare(_T("1bb11")));

	// erase string 
	char_string4 = _T("12345aa1234512345");
	char_string4.erase(5, 2);
	EXTL_ASSERT(!char_string4.compare(_T("123451234512345")));
	char_string4.erase(char_string4.begin());
	EXTL_ASSERT(!char_string4.compare(_T("23451234512345")));
	char_string4.erase(++char_string4.begin(), char_string4.end());
	EXTL_ASSERT(!char_string4.compare(_T("2")));

	char_string4 = _T("12345");
	char_string4.insert(0, _T("gg"));
	EXTL_ASSERT(!char_string4.compare(_T("gg12345")));
	char_string4.insert(2, _T("aa"));
	EXTL_ASSERT(!char_string4.compare(_T("ggaa12345")));
	char_string4.insert(4, _T('b'), 4);
	EXTL_ASSERT(!char_string4.compare(_T("ggaabbbb12345")));
	char_string4.insert(char_string4.begin(), _T('b'), 4);
	EXTL_ASSERT(!char_string4.compare(_T("bbbbggaabbbb12345")));
	char_string4.insert(char_string4.begin(), _T("gg"));
	EXTL_ASSERT(!char_string4.compare(_T("ggbbbbggaabbbb12345")));

	// Format string 
	char_string4.format(_T("123%d%s"), 456, _T("789"));
	EXTL_ASSERT(!char_string4.compare(_T("123456789")));
	char_string4.append_format(_T("123%d%s"), 456, _T("789"));
	EXTL_ASSERT(!char_string4.compare(_T("123456789123456789")));

	// Reverses string 
	char_string4 = _T("123456789");
	EXTL_ASSERT(!char_string4.compare(char_string4.reverse()));
	return 0;
}
int attached_string_test_ret = attached_string_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(attached_string_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_ATTACHED_STRING_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

