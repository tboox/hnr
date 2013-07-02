/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_list_test.h		
 *
 * Created:		08.08.25			
 * Updated:		08.08.25
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_BASIC_LIST_TEST_H
#define EXTL_CONTAINER_BASIC_LIST_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(basic_list_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */

static int basic_list_test()
{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_list<int>						list_type;
#else
	typedef basic_list			<	int
								,	allocator_selector<int>::allocator_type
								,	memory_traits_selector<int>::memory_traits_type
								,	initialiser_selector<int>::initialiser_type
								>				list_type;
#endif

	list_type lt1;
	EXTL_ASSERT(lt1.size() == 0);

	list_type lt2(10, 20);
	EXTL_ASSERT(lt2.size() == 20);
	EXTL_ASSERT(lt2.front() == 10);
	EXTL_ASSERT(lt2.back() == 10);

	lt2.push_front(1);
	lt2.push_back(1);
	EXTL_ASSERT(lt2.size() == 22);
	EXTL_ASSERT(lt2.front() == 1);
	EXTL_ASSERT(lt2.back() == 1);

	lt2.pop_front();
	lt2.pop_back();
	EXTL_ASSERT(lt2.size() == 20);
	EXTL_ASSERT(lt2.front() == 10);
	EXTL_ASSERT(lt2.back() == 10);

	lt1.swap(lt2);
	lt1.resize(100);
	EXTL_ASSERT(lt1.size() == 100);
	/*for (list_type::const_iterator p = lt1.begin(); p != lt1.end(); ++p)
	{
		printf("%d ", *p);
	}*/
	return 0;
}

int basic_list_test_ret = basic_list_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_list_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_BASIC_LIST_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

