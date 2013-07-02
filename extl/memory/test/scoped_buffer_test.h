/* ///////////////////////////////////////////////////////////////////////
 * File:		scoped_buffer_test.h		
 *
 * Created:		08.03.06			
 * Updated:		08.12.22
 *
 * Brief:		The Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MEMORY_SCOPED_BUFFER_TEST_H
#define EXTL_MEMORY_SCOPED_BUFFER_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../math/rand.h"
#include "../counter/clock_counter.h"
#ifndef EXTL_NO_STL
#	include <vector>
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(scoped_buffer_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct scoped_buffer_test_obj
{
	scoped_buffer_test_obj()
	{
		//printf("constructor\n");
	}
	~scoped_buffer_test_obj()
	{
		//printf("destructor\n");
	}
};
static int scoped_buffer_test()
{
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef scoped_buffer<int>									buffer_type;
	typedef scoped_buffer<e_tchar_t>							char_buffer_type;
	typedef scoped_buffer<scoped_buffer_test_obj, 1>			obj_buffer_type;

#else
	typedef scoped_buffer	<	int
							,	EXTL_MEMORY_SCOPED_BUFFER_DEFAULT_GROW_SIZE
							,	allocator_selector<int>::allocator_type
							,	memory_traits_selector<int>::memory_traits_type
							,	initialiser_selector<int>::initialiser_type
							>				buffer_type;
	typedef scoped_buffer	<	e_tchar_t
							,	EXTL_MEMORY_SCOPED_BUFFER_DEFAULT_GROW_SIZE
							,	allocator_selector<e_tchar_t>::allocator_type
							,	memory_traits_selector<e_tchar_t>::memory_traits_type
							,	initialiser_selector<e_tchar_t>::initialiser_type
							>				char_buffer_type;
	typedef scoped_buffer	<	scoped_buffer_test_obj
							,	EXTL_MEMORY_SCOPED_BUFFER_DEFAULT_GROW_SIZE
							,	allocator_selector<scoped_buffer_test_obj>::allocator_type
							,	memory_traits_selector<scoped_buffer_test_obj>::memory_traits_type
							,	initialiser_selector<scoped_buffer_test_obj>::initialiser_type
							>				obj_buffer_type;
#endif

	EXTL_TEST_TRACE(_T("/* //////////////////////////////////////////////////////////////////// */"));
	EXTL_TEST_TRACE(_T("scoped_buffer Test:\n"));

	clock_counter counter;
	volatile int i = 0;
	rand_selector::rand_type r1(100);
	rand_selector::rand_type r2(100);
	rand_selector::rand_type r3(100);

	// scoped_buffer<> test 
	buffer_type buf;
	counter.begin();
	for(i=0; i < 50000; i++)
	{	
		buf.resize(r1.generate(0, 256));
	}
	counter.end();
	EXTL_TEST_TRACE(_T("scoped_buffer<>::resize(0 - 256) time:%d ms"), counter.ms());

	buf.destroy();
	counter.begin();
	for(i=0; i < 50000; i++)
	{	
		buf.resize(r2.generate(0, 1024));
	}
	counter.end();
	EXTL_TEST_TRACE(_T("scoped_buffer<>::resize(0 - 1024) time:%d ms"), counter.ms());

	buf.destroy();
	counter.begin();
	for(i=0; i < 50000; i++)
	{	
		buf.resize(r3.generate(0, 8 * 1024));
	}
	counter.end();
	EXTL_TEST_TRACE(_T("scoped_buffer<>::resize(0 - 8 * 1024) time:%d ms\n"), counter.ms());

#ifndef EXTL_NO_STL
	// vector<> test 
	EXTL_NS_STD(vector)<int> vec;
	r1.reset();
	r2.reset();
	r3.reset();
	counter.begin();
	for(i=0; i < 50000; i++)
	{	
		vec.resize(r1.generate(0, 256));
	}
	counter.end();
	EXTL_TEST_TRACE(_T("vector<>::resize(0 - 256) time:%d ms"), counter.ms());

	vec.clear();
	counter.begin();
	for(i=0; i < 50000; i++)
	{	
		vec.resize(r2.generate(0, 1024));
	}
	counter.end();
	EXTL_TEST_TRACE(_T("vector<>::resize(0 - 1024) time:%d ms"), counter.ms());

	vec.clear();
	counter.begin();
	for(i=0; i < 50000; i++)
	{	
		vec.resize(r3.generate(0, 8 * 1024));
	}
	counter.end();
	EXTL_TEST_TRACE(_T("vector<>::resize(0 - 8 * 1024) time:%d ms\n"), counter.ms());
#endif
	buffer_type buf2;
	counter.begin();
	for(i=0; i < 100000; i++)
	{	
		buf2.swap(buf);
	}
	counter.end();
	EXTL_TEST_TRACE(_T("scoped_buffer<>::swap() time:%d ms"), counter.ms());

#ifndef EXTL_NO_STL
	EXTL_NS_STD(vector)<int> vec2;
	counter.begin();
	for(i=0; i < 100000; i++)
	{	
		vec2.swap(vec);
	}
	counter.end();
	EXTL_TEST_TRACE(_T("vector<>::swap() time:%d ms\n"), counter.ms());
#endif
	
	// char_buffer_type test 
	char_buffer_type b;
	b.assign(_T("123456789"), 10);
	EXTL_TEST_TRACE(_T("assgin() test:%s"), b.data());
	b.insert(b.begin(), _T('0'));
	EXTL_TEST_TRACE(_T("insert() test:%s"), b.data());
	b.pop_back(); // pop '\0' 
	b.push_back(_T('0'));
	b.push_back(_T('\0'));
	EXTL_TEST_TRACE(_T("pop_back and push_back() test:%s"), b.data());
	b.reverse(0, b.size() - 1);
	EXTL_TEST_TRACE(_T("reverse() test:%s"), b.data());

	obj_buffer_type objs;
	objs.push_back(scoped_buffer_test_obj());
	EXTL_ASSERT(objs.size() == 1);

	return 0;
}

int scoped_buffer_test_ret = scoped_buffer_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(scoped_buffer_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_SCOPED_BUFFER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

