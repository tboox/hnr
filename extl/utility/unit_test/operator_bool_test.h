/* ///////////////////////////////////////////////////////////////////////
 * File:		operator_bool_test.h		
 *
 * Created:		08.03.01				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_OPERATOR_BOOL_TEST_H
#define EXTL_UTILITY_OPERATOR_BOOL_TEST_H

#ifndef EXTL_UTILITY_OPERATOR_BOOL_H
#	error This file must be included of operator_bool.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct operator_bool_test
{
	struct test_ptr
	{
		EXTL_OPERATOR_BOOL_DEFINE_TYPE(test_ptr, safe_bool_t);

		operator safe_bool_t() const
		{
			return EXTL_OPERATOR_BOOL_RETURN_RESULT(1);
		}

		e_bool_t operator! () const
		{
			return e_false_v;
		}
	};

	struct non_ptr
	{
		operator e_bool_t() const
		{
			return e_true_v;
		}
	};

	operator_bool_test()
	{
		test_ptr p;
		EXTL_ASSERT(p);
		EXTL_ASSERT(p && 1);
		EXTL_ASSERT(p || 0);
		EXTL_ASSERT(!!p);

	#if	!defined(EXTL_COMPILER_IS_MSVC) || _MSC_VER >1200
		EXTL_ASSERT(!(p == NULL));
		EXTL_ASSERT(p != NULL);
	#endif

		/* Prohibit the promotion of the integer type*/
		/* int i = p + p; */

		/* non_ptr np; 
		EXTL_ASSERT(np != p); */
		
	}
};
#if !defined(EXTL_COMPILER_IS_BORLAND)
operator_bool_test g_operator_bool_test;
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_OPERATOR_BOOL_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
