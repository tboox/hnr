/* ///////////////////////////////////////////////////////////////////////
 * File:		stack_string_test.h		
 *
 * Created:		08.03.20					
 * Updated:		08.04.14	
 *
 * Brief: stack_string unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_STACK_STRING_TEST_H
#define EXTL_STRING_STACK_STRING_TEST_H

#ifndef EXTL_STRING_STACK_STRING_H
#	error This file must be included of stack_string.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(stack_string_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int stack_string_test()
{
	typedef stack_string char_stack_string;

	char_stack_string char_string0;
	char_stack_string char_string1(_T("char_string"));
	char_stack_string char_string2(char_string1);
	char_stack_string char_string3(char_string1, 4);
	char_stack_string char_string4(_T('a'), 5);
	char_stack_string char_string5(_T("char_string"), 4);

	EXTL_ASSERT(!char_string1.compare(_T("char_string")));
	EXTL_ASSERT(!char_string2.compare(char_string1));
	EXTL_ASSERT(!char_string4.compare(_T("aaaaaaaaa"), 5));
	EXTL_ASSERT(!char_string5.compare(_T("char")));

	EXTL_ASSERT(char_string0.is_empty());
	EXTL_ASSERT(!char_string1.is_empty());

	EXTL_ASSERT(char_string2.length() == char_string1.length());
	EXTL_ASSERT(char_string3.length() == 4);
	EXTL_ASSERT(char_string4.length() == 5);
	EXTL_ASSERT(char_string5.length() == 4);

	char_string4.resize(10);
	EXTL_ASSERT(char_string4.length() == 10);

	char_string4.resize(1);
	EXTL_ASSERT(!char_string4.compare(_T("a")));
	EXTL_ASSERT(char_string4.length() == 1);

	char_stack_string char_string6(_T("char_string"));
	char_stack_string char_string7(_T("char"));
	char_string7.swap(char_string6);
	EXTL_ASSERT(!char_string7.compare(_T("char_string")));
	EXTL_ASSERT(!char_string6.compare(_T("char")));

	EXTL_ASSERT(char_string6[0] == _T('c'));
	EXTL_ASSERT(char_string7.at(4) == _T('_'));

	char_string6.assign(_T("char_string"));
	char_string7.assign(char_string6, 4);
	EXTL_ASSERT(!char_string7.compare(_T("char")));
	char_string7.assign(_T("char_string"), 4);
	EXTL_ASSERT(!char_string7.compare(_T("char")));
	char_string7.assign(_T('a'), 4);
	EXTL_ASSERT(!char_string7.compare(_T("aaaa")));
	char_string7 = _T('a');
	EXTL_ASSERT(!char_string7.compare(_T("a")));

	char_string7 += _T('a');
	EXTL_ASSERT(!char_string7.compare(_T("aa")));
	char_string7.append(char_string6, 4);
	EXTL_ASSERT(!char_string7.compare(_T("aachar")));

	char_stack_string char_string8(_T("123456789"));
	char_stack_string char_string9(_T("123456789"));
	char_stack_string char_string10(_T("987654321"));

	char_stack_string char_string11(_T("ABCDabcd987654321"));
	char_string11.to_lower();
	EXTL_ASSERT(!char_string11.compare(_T("abcdabcd987654321")));
	char_string11.to_upper();
	EXTL_ASSERT(!char_string11.compare(_T("ABCDABCD987654321")));
	EXTL_ASSERT(!char_string11.compare_nocase(_T("abcdabcd987654321")));

	EXTL_ASSERT(char_string8 == char_string9);
	EXTL_ASSERT(char_string8 != char_string10);

	EXTL_ASSERT(char_string8 < char_string10);
	EXTL_ASSERT(char_string10 > char_string8);
	EXTL_ASSERT(char_string8 <= char_string10);
	EXTL_ASSERT(char_string10 >= char_string8);

	EXTL_ASSERT(_T("123456789") == char_string9);
	EXTL_ASSERT(_T("123456789") != char_string10);

	EXTL_ASSERT(char_string8 == _T("123456789"));
	EXTL_ASSERT(char_string8 != _T("987654321"));

	EXTL_ASSERT(char_string8 < _T("987654321"));
	EXTL_ASSERT(char_string10 > _T("123456789"));
	EXTL_ASSERT(char_string8 <= _T("987654321"));
	EXTL_ASSERT(char_string10 >= _T("123456789"));

	EXTL_ASSERT(_T("123456789") < char_string10);
	EXTL_ASSERT(_T("987654321") > char_string8);
	EXTL_ASSERT(_T("123456789") <= char_string10);
	EXTL_ASSERT(_T("987654321") >= char_string8);

	char_string0 = _T("1234");
	char_string1 = _T("5678");
	char_string2 = char_string0 + char_string1 + _T("9");
	EXTL_ASSERT(!char_string2.compare(_T("123456789")));

	char_string2 = _T("123456789");
	EXTL_ASSERT(!char_string2.left(4).compare(_T("1234")));
	EXTL_ASSERT(!char_string2.right(4).compare(_T("6789")));

	// iterator test 
	char_stack_string char_string12(_T("123456789"));
	char_stack_string char_string13(char_string12.begin(), char_string12.end());
	char_string13.assign(char_string13.rbegin(), char_string13.rend());
	EXTL_ASSERT(!char_string13.compare(_T("987654321")));
	EXTL_ASSERT(!char_string13.compare(char_string12.rbegin(), char_string12.rend()));
	char_string13.append(char_string12.rbegin(), char_string12.rend());
	EXTL_ASSERT(!char_string13.compare(_T("987654321987654321")));

	e_tchar_t p[]=_T("123456789");
	char_stack_string char_string14(p, p + 9);
	EXTL_ASSERT(!char_string14.compare(_T("123456789")));


	// critical value test 
	typedef basic_stack_string	<	e_tchar_t
								,	5
								,	string_traits<e_tchar_t, std_char_traits<e_tchar_t> >
								> char_tiny_stack_string;
	char_tiny_stack_string tts(_T("12345"));
	EXTL_ASSERT(!tts.compare(_T("12345")));

	// replace operation 
	char_string2 = _T("12345");

	char_string2.replace(0, 1, _T("aaa"), 3);
	EXTL_ASSERT(!char_string2.compare(_T("aaa2345")));

	char_string2.replace(7, 0, _T("aaa"), 3);
	EXTL_ASSERT(!char_string2.compare(_T("aaa2345aaa")));

	char_string2.replace(0, 3, char_string2.c_str() + 3, 4);
	EXTL_ASSERT(!char_string2.compare(_T("23452345aaa")));

	char_string2.replace(0, 4, char_string2.c_str() + 8, 3);
	EXTL_ASSERT(!char_string2.compare(_T("aaa2345aaa")));

	char_string2.replace(7, 3, char_string2.c_str(), 7);
	EXTL_ASSERT(!char_string2.compare(_T("aaa2345aaa2345")));

	char_string2.replace(3, 4, char_string2.c_str() + 5, 9);
	EXTL_ASSERT(!char_string2.compare(_T("aaa45aaa2345aaa2345")));

	char_string2.replace(8, 4, char_string2.c_str() + 5, 14);
	EXTL_ASSERT(!char_string2.compare(_T("aaa45aaaaaa2345aaa2345aaa2345")));


	char_string3 = _T("12345");

	char_string3.replace(0, 1, _T("aaa"));
	EXTL_ASSERT(!char_string3.compare(_T("aaa2345")));

	char_string3.replace(char_string3.begin(), char_string3.end(), char_string3);
	EXTL_ASSERT(!char_string3.compare(_T("aaa2345")));

	char_string3.replace(char_string3.begin(), char_string3.end(), _T('a'));
	EXTL_ASSERT(!char_string3.compare(_T("a")));

	char_string3.replace(char_string3.begin(), _T('a'), 2);
	EXTL_ASSERT(!char_string3.compare(_T("aa")));

	char_string3.replace(char_string3.begin(), char_string3.end(), char_string3.begin(), char_string3.end());
	EXTL_ASSERT(!char_string3.compare(_T("aa")));

	// find string 
	char_string3 = _T("12345aa12345");
	EXTL_ASSERT(5 == char_string3.find(_T("aa")));
	EXTL_ASSERT(char_string3.fof() == char_string3.find(_T("aa4545")));
	EXTL_ASSERT(5 == char_string3.find(_T('a')));

	// rfind string 
	char_string3 = _T("12345aa12345");
	EXTL_ASSERT(7 == char_string3.rfind(_T("12345")));
	EXTL_ASSERT(char_string3.fof() == char_string3.rfind(_T("123dsad45aa")));
	EXTL_ASSERT(6 == char_string3.rfind(_T('a')));

	// replace string in the whole context 
	char_string3 = _T("12345aa1234512345");
	char_string3.replace_all(_T("12345"), _T("1"));
	EXTL_ASSERT(!char_string3.compare(_T("1aa11")));
	char_string3.replace_all(_T('a'), _T('b'));
	EXTL_ASSERT(!char_string3.compare(_T("1bb11")));

	// erase string 
	char_string3 = _T("12345aa1234512345");
	char_string3.erase(5, 2);
	EXTL_ASSERT(!char_string3.compare(_T("123451234512345")));
	char_string3.erase(char_string3.begin());
	EXTL_ASSERT(!char_string3.compare(_T("23451234512345")));
	char_string3.erase(++char_string3.begin(), char_string3.end());
	EXTL_ASSERT(!char_string3.compare(_T("2")));

	char_string3 = _T("12345");
	char_string3.insert(0, _T("gg"));
	EXTL_ASSERT(!char_string3.compare(_T("gg12345")));
	char_string3.insert(2, _T("aa"));
	EXTL_ASSERT(!char_string3.compare(_T("ggaa12345")));
	char_string3.insert(4, _T('b'), 4);
	EXTL_ASSERT(!char_string3.compare(_T("ggaabbbb12345")));
	char_string3.insert(char_string3.begin(), _T('b'), 4);
	EXTL_ASSERT(!char_string3.compare(_T("bbbbggaabbbb12345")));
	char_string3.insert(char_string3.begin(), _T("gg"));
	EXTL_ASSERT(!char_string3.compare(_T("ggbbbbggaabbbb12345")));

	// Format string 
	char_string3.format(_T("123%d%s"), 456, _T("789"));
	EXTL_ASSERT(!char_string3.compare(_T("123456789")));
	char_string3.append_format(_T("123%d%s"), 456, _T("789"));
	EXTL_ASSERT(!char_string3.compare(_T("123456789123456789")));

	// Reverses string 
	char_string3 = _T("123456789");
	EXTL_ASSERT(!char_string3.compare(char_string3.reverse()));
	return 0;
}
int stack_string_test_ret = stack_string_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(stack_string_test)
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_STACK_STRING_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

