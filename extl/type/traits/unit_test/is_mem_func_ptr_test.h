/* ///////////////////////////////////////////////////////////////////////
 * File:		is_mem_func_ptr_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.09	
 *
 * Brief: is_mem_func_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_H
#	error This file must be included of is_mem_func_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

#ifndef EXTL_COMPILER_IS_BORLAND
#	define EXTL_IS_MEM_FUNC_PTR_TEST_CV_(s)	\
				EXTL_MUST_BE_CV_MEM_FUNC_PTR(s); \
				EXTL_MUST_BE_CV_MEM_FUNC_PTR(s const); \
				EXTL_MUST_BE_CV_MEM_FUNC_PTR(s volatile); \
				EXTL_MUST_BE_CV_MEM_FUNC_PTR(s const volatile); 
#	define EXTL_IS_MEM_FUNC_PTR_TEST_(arglist)	\
				EXTL_IS_MEM_FUNC_PTR_TEST_CV_(int (is_mem_func_ptr_test::*)(arglist)) \
				EXTL_IS_MEM_FUNC_PTR_TEST_CV_(int (EXTL_CDECL is_mem_func_ptr_test::*)(arglist)) \
				EXTL_IS_MEM_FUNC_PTR_TEST_CV_(int (EXTL_FASTCALL is_mem_func_ptr_test::*)(arglist)) \
				EXTL_IS_MEM_FUNC_PTR_TEST_CV_(int (EXTL_STDCALL is_mem_func_ptr_test::*)(arglist)) 

#else
#	define EXTL_IS_MEM_FUNC_PTR_TEST_CV_(s)	\
				do{s; EXTL_MUST_BE_CV_MEM_FUNC_PTR(p);}while(0); \
				do{s const; EXTL_MUST_BE_CV_MEM_FUNC_PTR(p);}while(0); \
				do{s volatile; EXTL_MUST_BE_CV_MEM_FUNC_PTR(p);}while(0); \
				do{s const volatile; EXTL_MUST_BE_CV_MEM_FUNC_PTR(p);}while(0); 

#	define EXTL_IS_MEM_FUNC_PTR_TEST_(arglist)	\
				EXTL_IS_MEM_FUNC_PTR_TEST_CV_(typedef int (is_mem_func_ptr_test::*p)(arglist)) \
				EXTL_IS_MEM_FUNC_PTR_TEST_CV_(typedef int EXTL_CDECL (is_mem_func_ptr_test::*p)(arglist)) \
				EXTL_IS_MEM_FUNC_PTR_TEST_CV_(typedef int EXTL_FASTCALL (is_mem_func_ptr_test::*p)(arglist)) \
				EXTL_IS_MEM_FUNC_PTR_TEST_CV_(typedef int EXTL_STDCALL (is_mem_func_ptr_test::*p)(arglist))
#endif

#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_0
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_1	int
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_2	int, int
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_3	int, int ,int
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_4	int, int ,int ,int
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_5	int, int ,int ,int ,int
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_6	int, int ,int ,int ,int ,int
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_7	int, int ,int ,int ,int ,int ,int
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_8	int, int ,int ,int ,int ,int ,int ,int
#define EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_9	int, int ,int ,int ,int ,int ,int ,int ,int

#define EXTL_IS_MEM_FUNC_PTR_TEST(num)						EXTL_IS_MEM_FUNC_PTR_TEST_( EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_##num )
#define EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(num)		EXTL_IS_MEM_FUNC_PTR_TEST_( EXTL_IS_MEM_FUNC_PTR_TEST_ARGLIST_##num ... )

struct is_mem_func_ptr_test
{
	is_mem_func_ptr_test()
	{
		EXTL_IS_MEM_FUNC_PTR_TEST(0) /* 0 params */
		EXTL_IS_MEM_FUNC_PTR_TEST(1) /* 1 params */
		EXTL_IS_MEM_FUNC_PTR_TEST(2) /* 2 params */
		EXTL_IS_MEM_FUNC_PTR_TEST(3) /* 3 params */
		EXTL_IS_MEM_FUNC_PTR_TEST(4) /* 4 params */
		EXTL_IS_MEM_FUNC_PTR_TEST(5) /* 5 params */
		EXTL_IS_MEM_FUNC_PTR_TEST(6) /* 6 params */
		EXTL_IS_MEM_FUNC_PTR_TEST(7) /* 7 params */
		EXTL_IS_MEM_FUNC_PTR_TEST(8) /* 8 params */

#if !defined(EXTL_COMPILER_IS_MSVC) || (_MSC_VER > 1200)
		EXTL_IS_MEM_FUNC_PTR_TEST(9) /* 9 params */
#endif

	/* function testing with ... */
#ifdef EXTL_ELLIPSIS_IN_MEM_FUNC_TESTING_SUPPORT	

		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(0) /* 0 params */
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(1) /* 1 params */
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(2) /* 2 params */
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(3) /* 3 params */
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(4) /* 4 params */
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(5) /* 5 params */
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(6) /* 6 params */
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(7) /* 7 params */
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(8) /* 8 params */

#	if !defined(EXTL_COMPILER_IS_MSVC) || (_MSC_VER > 1200)
		EXTL_IS_MEM_FUNC_PTR_TEST_WITH_ELLIPSIS(9) /* 9 params */
#	endif
#endif


#ifndef EXTL_COMPILER_IS_BORLAND
		EXTL_MUST_NOT_BE_CV_MEM_FUNC_PTR(int);
		EXTL_MUST_NOT_BE_CV_MEM_FUNC_PTR(int &);
		EXTL_MUST_NOT_BE_CV_MEM_FUNC_PTR(int (*)());
		EXTL_MUST_NOT_BE_CV_MEM_FUNC_PTR(int *);
		EXTL_MUST_NOT_BE_CV_MEM_FUNC_PTR(int [10]);
		EXTL_MUST_NOT_BE_CV_MEM_FUNC_PTR(void *);
		EXTL_MUST_NOT_BE_CV_MEM_FUNC_PTR(void);
#endif

	}
};


/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
