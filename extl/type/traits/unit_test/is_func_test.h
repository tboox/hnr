/* ///////////////////////////////////////////////////////////////////////
 * File:		is_func_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.09	
 *
 * Brief: is_func unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_FUNC_H
#	error This file must be included of is_func.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#ifndef EXTL_COMPILER_IS_VECTORC
#	define EXTL_IS_FUNC_TEST_(ellipsis, num, arglist)	\
				typedef int (is_func_test_##ellipsis##_1_##num)(arglist); \
				EXTL_MUST_BE_FUNC(is_func_test_##ellipsis##_1_##num); \
				typedef int (EXTL_CDECL is_func_test_##ellipsis##_2_##num)(arglist); \
				EXTL_MUST_BE_FUNC(is_func_test_##ellipsis##_2_##num); \
				typedef int (EXTL_FASTCALL is_func_test_##ellipsis##_3_##num)(arglist); \
				EXTL_MUST_BE_FUNC(is_func_test_##ellipsis##_3_##num); \
				typedef int (EXTL_STDCALL is_func_test_##ellipsis##_4_##num)(arglist); \
				EXTL_MUST_BE_FUNC(is_func_test_##ellipsis##_4_##num); 
#else 
#	define EXTL_IS_FUNC_TEST_(ellipsis, num, arglist)	\
				typedef int (is_func_test_##ellipsis##_1_##num)(arglist); \
				EXTL_MUST_BE_FUNC(is_func_test_##ellipsis##_1_##num); \
				typedef int (EXTL_CDECL is_func_test_##ellipsis##_2_##num)(arglist); \
				EXTL_MUST_BE_FUNC(is_func_test_##ellipsis##_2_##num); 
#endif


#define EXTL_IS_FUNC_TEST_ARGLIST_0
#define EXTL_IS_FUNC_TEST_ARGLIST_1	int
#define EXTL_IS_FUNC_TEST_ARGLIST_2	int, int
#define EXTL_IS_FUNC_TEST_ARGLIST_3	int, int ,int
#define EXTL_IS_FUNC_TEST_ARGLIST_4	int, int ,int ,int
#define EXTL_IS_FUNC_TEST_ARGLIST_5	int, int ,int ,int ,int
#define EXTL_IS_FUNC_TEST_ARGLIST_6	int, int ,int ,int ,int ,int
#define EXTL_IS_FUNC_TEST_ARGLIST_7	int, int ,int ,int ,int ,int ,int
#define EXTL_IS_FUNC_TEST_ARGLIST_8	int, int ,int ,int ,int ,int ,int ,int
#define EXTL_IS_FUNC_TEST_ARGLIST_9	int, int ,int ,int ,int ,int ,int ,int ,int


#define EXTL_IS_FUNC_TEST(num)					EXTL_IS_FUNC_TEST_( no_ellipsis, num, EXTL_IS_FUNC_TEST_ARGLIST_##num )
#define EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(num)	EXTL_IS_FUNC_TEST_( with_ellipsis, num, EXTL_IS_FUNC_TEST_ARGLIST_##num ... )

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_func_test()
{
	EXTL_IS_FUNC_TEST(0) /* 0 params */
	EXTL_IS_FUNC_TEST(1) /* 1 params */
	EXTL_IS_FUNC_TEST(2) /* 2 params */
	EXTL_IS_FUNC_TEST(3) /* 3 params */
	EXTL_IS_FUNC_TEST(4) /* 4 params */
	EXTL_IS_FUNC_TEST(5) /* 5 params */
	EXTL_IS_FUNC_TEST(6) /* 6 params */
	EXTL_IS_FUNC_TEST(7) /* 7 params */
	EXTL_IS_FUNC_TEST(8) /* 8 params */
	EXTL_IS_FUNC_TEST(9) /* 9 params */

/* function testing with ... */
#ifdef EXTL_ELLIPSIS_IN_FUNC_TESTING_SUPPORT	

	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(0) /* 0 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(1) /* 1 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(2) /* 2 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(3) /* 3 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(4) /* 4 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(5) /* 5 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(6) /* 6 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(7) /* 7 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(8) /* 8 params */
	EXTL_IS_FUNC_TEST_WITH_ELLIPSIS(9) /* 9 params */

#endif

#ifndef EXTL_COMPILER_IS_BORLAND
	EXTL_MUST_NOT_BE_CV_FUNC(int);
	//EXTL_MUST_NOT_BE_CV_FUNC(int &);
	EXTL_MUST_NOT_BE_CV_FUNC(int *);
	EXTL_MUST_NOT_BE_CV_FUNC(int [10]);
	EXTL_MUST_NOT_BE_CV_FUNC(void *);
	EXTL_MUST_NOT_BE_CV_FUNC(void);
#endif

}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
