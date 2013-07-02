/* ///////////////////////////////////////////////////////////////////////
 * File:		operators_test.h		
 *
 * Created:		08.03.30			
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_OPERATORS_TEST_H
#define EXTL_UTILITY_OPERATORS_TEST_H

#ifndef EXTL_UTILITY_OPERATORS_H
#	error This file must be included of operators.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
#	define EXTL_OPERATORS_TEST_DEFAULT_ARG	
#else
#	define EXTL_OPERATORS_TEST_DEFAULT_ARG	,operators_base_<operators_test_class >
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct operators_test_class
	: private operators_less_1_<operators_test_class,
				operators_less_2_<operators_test_class, int,
					operators_equal_1_< operators_test_class,
						operators_equal_2_< operators_test_class, int,
							operators_add_1_< operators_test_class,
								operators_add_2_< operators_test_class, int,
									operators_post_inc_< operators_test_class,
										operators_post_dec_< operators_test_class EXTL_OPERATORS_TEST_DEFAULT_ARG
	> > > > > > > > 

	/* Space bloat */
	/*: private operators_less_1_< operators_test_class EXTL_OPERATORS_TEST_DEFAULT_ARG>
	, private operators_less_2_< operators_test_class, int EXTL_OPERATORS_TEST_DEFAULT_ARG>
	, private operators_equal_1_< operators_test_class EXTL_OPERATORS_TEST_DEFAULT_ARG>
	, private operators_equal_2_< operators_test_class, int EXTL_OPERATORS_TEST_DEFAULT_ARG>
	, private operators_add_1_< operators_test_class EXTL_OPERATORS_TEST_DEFAULT_ARG>
	, private operators_add_2_< operators_test_class, int EXTL_OPERATORS_TEST_DEFAULT_ARG>
	, private operators_post_inc_< operators_test_class EXTL_OPERATORS_TEST_DEFAULT_ARG>
	, private operators_post_dec_< operators_test_class EXTL_OPERATORS_TEST_DEFAULT_ARG>*/
{
	typedef operators_test_class class_type;
	operators_test_class(int n)
		: a(n)
	{}

	e_bool_t operator<(class_type const& rhs) const /* must add const-qualified */
	{return a < rhs.a;}
	e_bool_t operator<(int const& b) const 
	{return a < b;}

	e_bool_t operator==(class_type const& rhs) const 
	{return a == rhs.a;}
	e_bool_t operator==(int b) const 
	{return a == b;}

	class_type& operator+=(class_type const& rhs){a += rhs.a; return *this;}
	class_type& operator+=(int b){a += b; return *this;}
	
	class_type& operator++(){++a; return *this;}
	class_type& operator--(){--a; return *this;}
	
	int const& operator*() const {return a;}

	private:
		int a;
};
struct operators_test
{
	operators_test()
	{
		operators_test_class a(10);
		operators_test_class b(11);
		operators_test_class c(10);

		EXTL_ASSERT(a != b);
		EXTL_ASSERT(a != b);
		EXTL_ASSERT(a != 15);
		EXTL_ASSERT(15 != a);
		EXTL_ASSERT(16 > a);
		EXTL_ASSERT(10 >= a);
		EXTL_ASSERT((a + 10) == 20);
		EXTL_ASSERT(a++ == 10);
		EXTL_ASSERT(a-- == 11);
		EXTL_ASSERT(a == 10);
		//EXTL_ASSERT(&*a == a.operator->());
	}
};

operators_test g_operators_test;

#undef EXTL_OPERATORS_TEST_DEFAULT_ARG
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_OPERATORS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
