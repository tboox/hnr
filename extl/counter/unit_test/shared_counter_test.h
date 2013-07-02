/* ///////////////////////////////////////////////////////////////////////
 * File:		shared_counter_test.h		
 *
 * Created:		08.02.19				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SHARED_COUNTER_TEST_H
#define EXTL_SHARED_COUNTER_TEST_H

#ifndef EXTL_SHARED_COUNTER_H
#	error This file must be included of shared_counter.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct shared_counter_test 
{
	struct resource_deleter
	{
		void operator()(e_int_t* res)
		{
			if(NULL != res) *res = 0;
		}
	};
	struct res_owner
	{
		public:
			typedef res_owner		class_type;

		public:
			res_owner()
				: resource(NULL), sc()
			{
			}
			res_owner(e_int_t* res)
				: resource(res), sc(res)
			{
			}
		#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT	
			typedef shared_counter<e_int_t, resource_deleter>	shared_counter_type;
		#else
			typedef shared_counter	<	e_int_t
									,	resource_deleter
									,	synch_traits_selector::synch_traits_type	
									,	allocator_selector<	e_byte_t >::allocator_type
									>	shared_counter_type;
		#endif

		public:
			e_int_t* resource;
			shared_counter_type sc;
	};

	shared_counter_test()
	{
		res_owner  sct1(new e_int_t(10)), sct2;
		EXTL_ASSERT(sct1.sc.count() == 1);
		EXTL_ASSERT(sct2.sc.count() == 0);

		sct2 = sct1;
		EXTL_ASSERT(sct1.sc.count() == 2);
		EXTL_ASSERT(sct2.sc.count() == 2);
		EXTL_ASSERT(*sct1.resource == 10);
		EXTL_ASSERT(*sct2.resource == 10);

		sct1 = sct1;
		EXTL_ASSERT(sct1.sc.count() == 2);
		EXTL_ASSERT(sct2.sc.count() == 2);
		EXTL_ASSERT(*sct1.resource == 10);
		EXTL_ASSERT(*sct2.resource == 10);

		sct1.sc.swap(sct2.sc);
		EXTL_ASSERT(sct1.sc.count() == 2);
		EXTL_ASSERT(sct2.sc.count() == 2);
		EXTL_ASSERT(*sct1.resource == 10);
		EXTL_ASSERT(*sct2.resource == 10);

		e_int_t* pRes = NULL;
		{
			res_owner sct3(new e_int_t(15));
			EXTL_ASSERT(*sct3.resource == 15);
			pRes = sct3.resource;
		}

		EXTL_ASSERT(*pRes == 0);
		delete pRes;

	}
};

shared_counter_test g_shared_counter_test;

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SHARED_COUNTER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
