/* ///////////////////////////////////////////////////////////////////////
 * File:		sort_test.h		
 *
 * Created:		08.02.25			
 * Updated:		08.04.15	
 *
 * Brief:		The Sort Algorithm Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_SORT_TEST_H
#define EXTL_ALGORITHM_SORT_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../../utility/element_num.h"
#include "../../functional/functional.h"
#include "../../memory/buffer.h"
#include "../../counter/counter.h"
#include "../../math/math.h"

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(sort_test)

struct sort_test
{
	typedef buffer_selector<int>::buffer_type	buffer_type;
	void rand_make(linear_rand& r, buffer_type& buf)
	{
		r.reset();
		for (buffer_type::iterator p = buf.begin(); p != buf.end(); ++p)
		{
			*p = r.generate(0, 100);
		}
	}

	void bubble_sort_test(clock_counter& t, linear_rand& r, buffer_type& buf)
	{
		e_size_t n = 10;
		if (buf.size() <= 64) n = 100000;
		if (buf.size() <= 512) n = 10000;
		if (buf.size() <= 2048) n = 500;
		if (buf.size() <= 4096) n = 20;

		rand_make(r, buf);
		t.begin();
		for (e_size_t i = 0; i < n; ++i)
			bubble_sort(buf.begin(), buf.end());
		t.end();
		EXTL_TEST_TRACE(_T("bubble_sort(%d) time: %f ms"), buf.size(), e_float_t(t.ms()) / n);
	}

	void insertion_sort_test(clock_counter& t, linear_rand& r, buffer_type& buf)
	{
		e_size_t n = 10;
		if (buf.size() <= 64) n = 100000;
		if (buf.size() <= 512) n = 10000;
		if (buf.size() <= 2048) n = 500;
		if (buf.size() <= 4096) n = 20;

		rand_make(r, buf);
		t.begin();
		for (e_size_t i = 0; i < n; ++i)
			insertion_sort(buf.begin(), buf.end());
		t.end();
		EXTL_TEST_TRACE(_T("insertion_sort(%d) time: %f ms"), buf.size(), e_float_t(t.ms()) / n);
	}

	void heap_sort_test(clock_counter& t, linear_rand& r, buffer_type& buf)
	{
		e_size_t n = 10;
		if (buf.size() <= 64) n = 100000;
		if (buf.size() <= 512) n = 10000;
		if (buf.size() <= 2048) n = 500;
		if (buf.size() <= 4096) n = 20;

		rand_make(r, buf);
		t.begin();
		for (e_size_t i = 0; i < n; ++i)
			heap_sort(buf.begin(), buf.end());
		t.end();
		EXTL_TEST_TRACE(_T("heap_sort(%d) time: %f ms"), buf.size(), e_float_t(t.ms()) / n);
	}

	sort_test()
	{
		EXTL_TEST_TRACE(_T("sort test:"));
		EXTL_TEST_TRACE(_T("///////////////////////////////////////////////////////////////////////"));

	#ifdef EXTL_ITERATOR_POINTER_AS_ITERATOR_SUPPORT
		EXTL_TEST_TRACE(_T("sort:\t\t\t568197555645645623687106443210"));

		#define EXTL_SORT_TEST_STR	_T("568197555645645623687106443210")

		// in ascending order
		e_tchar_t bubble_s1[] = EXTL_SORT_TEST_STR;
		e_size_t top_n = 5;
		bubble_sort(bubble_s1, bubble_s1 + EXTL_ELEMENT_NUM(bubble_s1) - 1);
		EXTL_TEST_TRACE(_T("bubble_sort:\t\t%s"), bubble_s1);

		e_tchar_t insertion_s1[] = EXTL_SORT_TEST_STR;
		insertion_sort(insertion_s1, insertion_s1 + EXTL_ELEMENT_NUM(insertion_s1) - 1);
		EXTL_TEST_TRACE(_T("insertion_sort:\t\t%s"), insertion_s1);

		e_tchar_t heap_s1[] = EXTL_SORT_TEST_STR;
		heap_sort(heap_s1, heap_s1 + EXTL_ELEMENT_NUM(heap_s1) - 1);
		EXTL_TEST_TRACE(_T("heap_sort:\t\t%s"), heap_s1);

		e_tchar_t heap_s2[] = EXTL_SORT_TEST_STR;
		heap_sort_top_n(heap_s2, heap_s2 + EXTL_ELEMENT_NUM(heap_s2) - 1, top_n, std_greater<e_tchar_t>());
		EXTL_TEST_TRACE(_T("heap_sort_top_n(%d):\t%s"), top_n, heap_s2);

		// in descending order
		e_tchar_t bubble_s2[] = EXTL_SORT_TEST_STR;
		bubble_sort(bubble_s2, bubble_s2 + EXTL_ELEMENT_NUM(bubble_s2) - 1, std_greater<e_tchar_t>());
		EXTL_TEST_TRACE(_T("\nbubble_sort:\t\t%s"), bubble_s2);

		e_tchar_t insertion_s2[] = EXTL_SORT_TEST_STR;
		insertion_sort(insertion_s2, insertion_s2 + EXTL_ELEMENT_NUM(insertion_s2) - 1, std_greater<e_tchar_t>());
		EXTL_TEST_TRACE(_T("insertion_sort:\t\t%s"), insertion_s2);

		e_tchar_t heap_s3[] = EXTL_SORT_TEST_STR;
		heap_sort(heap_s3, heap_s3 + EXTL_ELEMENT_NUM(heap_s3) - 1, std_greater<e_tchar_t>());
		EXTL_TEST_TRACE(_T("heap_sort:\t\t%s"), heap_s3);

		e_tchar_t heap_s4[] = EXTL_SORT_TEST_STR;
		heap_sort_top_n(heap_s4, heap_s4 + EXTL_ELEMENT_NUM(heap_s4) - 1, top_n);
		EXTL_TEST_TRACE(_T("heap_sort_top_n(%d):\t%s"), top_n, heap_s4);

		
	#endif

		// performance test
	#ifndef EXTL_DEBUG
		clock_counter t;
		linear_rand	r;

		buffer_type	buf32(32);
		buffer_type	buf64(64);
		buffer_type	buf128(128);
		buffer_type	buf512(512);
		buffer_type	buf1024(1024);
		buffer_type	buf2048(2048);
		buffer_type	buf4096(4096);
		buffer_type	buf8192(8192);
		buffer_type	buf16384(16384);
		buffer_type	buf32768(32768);


		EXTL_TEST_TRACE(_T("\nheap_sort performance test:"));
		heap_sort_test(t, r, buf32);
		heap_sort_test(t, r, buf64);
		heap_sort_test(t, r, buf128);
		heap_sort_test(t, r, buf512);
		heap_sort_test(t, r, buf1024);
		heap_sort_test(t, r, buf2048);
		heap_sort_test(t, r, buf4096);
		heap_sort_test(t, r, buf8192);
		heap_sort_test(t, r, buf16384);
		heap_sort_test(t, r, buf32768);

		EXTL_TEST_TRACE(_T("\nbubble_sort performance test:"));
		bubble_sort_test(t, r, buf32);
		bubble_sort_test(t, r, buf64);
		bubble_sort_test(t, r, buf128);
		bubble_sort_test(t, r, buf512);
		bubble_sort_test(t, r, buf1024);
		bubble_sort_test(t, r, buf2048);

		EXTL_TEST_TRACE(_T("\ninsertion_sort performance test:"));
		insertion_sort_test(t, r, buf32);
		insertion_sort_test(t, r, buf64);
		insertion_sort_test(t, r, buf128);
		insertion_sort_test(t, r, buf512);
		insertion_sort_test(t, r, buf1024);
		insertion_sort_test(t, r, buf2048);
	#endif
	}
};

sort_test g_sort_test;

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(sort_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_SORT_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
