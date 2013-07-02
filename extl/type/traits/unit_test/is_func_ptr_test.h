/* ///////////////////////////////////////////////////////////////////////
 * File:		is_func_ptr_test.h		
 *
 * Created:		08.02.02				
 * Updated:		08.07.09	
 *
 * Brief: is_func_ptr unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_FUNC_PTR_H
#	error This file must be included of is_func_ptr.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#ifndef EXTL_COMPILER_IS_BORLAND

#	ifdef EXTL_COMPILER_IS_VECTORC
#		define EXTL_IS_FUNC_PTR_TEST_(arglist)	\
				EXTL_MUST_BE_FUNC_PTR(int (*)(arglist)); \
				EXTL_MUST_BE_FUNC_PTR(int (EXTL_CDECL *)(arglist)); \
				EXTL_MUST_BE_FUNC_PTR(int (EXTL_FASTCALL *)(arglist)); \
				EXTL_MUST_BE_FUNC_PTR(int (EXTL_STDCALL *)(arglist)); 
#	else
#		define EXTL_IS_FUNC_PTR_TEST_(arglist)	\
				EXTL_MUST_BE_CV_FUNC_PTR(int (*)(arglist)); \
				EXTL_MUST_BE_CV_FUNC_PTR(int (EXTL_CDECL *)(arglist)); \
				EXTL_MUST_BE_CV_FUNC_PTR(int (EXTL_FASTCALL *)(arglist)); \
				EXTL_MUST_BE_CV_FUNC_PTR(int (EXTL_STDCALL *)(arglist)); 
#	endif

#else

#define EXTL_IS_FUNC_PTR_TEST_(arglist)	\
								do{typedef int (*p)(arglist); \
								EXTL_MUST_BE_CV_FUNC_PTR(p);}while(0); \
								do{typedef int (EXTL_CDECL *p)(arglist); \
								EXTL_MUST_BE_CV_FUNC_PTR(p);}while(0); \
								do{typedef int (EXTL_FASTCALL *p)(arglist); \
								EXTL_MUST_BE_CV_FUNC_PTR(p);}while(0); \
								do{typedef int (EXTL_STDCALL *p)(arglist); \
								EXTL_MUST_BE_CV_FUNC_PTR(p);}while(0);
		
#endif


#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_0
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_1	int
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_2	int, int
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_3	int, int ,int
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_4	int, int ,int ,int
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_5	int, int ,int ,int ,int
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_6	int, int ,int ,int ,int ,int
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_7	int, int ,int ,int ,int ,int ,int
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_8	int, int ,int ,int ,int ,int ,int ,int
#define EXTL_IS_FUNC_PTR_TEST_ARGLIST_9	int, int ,int ,int ,int ,int ,int ,int ,int

#define EXTL_IS_FUNC_PTR_TEST(num)						EXTL_IS_FUNC_PTR_TEST_( EXTL_IS_FUNC_PTR_TEST_ARGLIST_##num )
#define EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(num)		EXTL_IS_FUNC_PTR_TEST_( EXTL_IS_FUNC_PTR_TEST_ARGLIST_##num ... )

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_func_ptr_test()
{
	EXTL_IS_FUNC_PTR_TEST(0) /* 0 params */
	EXTL_IS_FUNC_PTR_TEST(1) /* 1 params */
	EXTL_IS_FUNC_PTR_TEST(2) /* 2 params */
	EXTL_IS_FUNC_PTR_TEST(3) /* 3 params */
	EXTL_IS_FUNC_PTR_TEST(4) /* 4 params */
	EXTL_IS_FUNC_PTR_TEST(5) /* 5 params */
	EXTL_IS_FUNC_PTR_TEST(6) /* 6 params */
	EXTL_IS_FUNC_PTR_TEST(7) /* 7 params */
	EXTL_IS_FUNC_PTR_TEST(8) /* 8 params */
	EXTL_IS_FUNC_PTR_TEST(9) /* 9 params */

/* function testing with ... */
#ifdef EXTL_ELLIPSIS_IN_FUNC_TESTING_SUPPORT	

	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(0) /* 0 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(1) /* 1 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(2) /* 2 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(3) /* 3 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(4) /* 4 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(5) /* 5 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(6) /* 6 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(7) /* 7 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(8) /* 8 params */
	EXTL_IS_FUNC_PTR_TEST_WITH_ELLIPSIS(9) /* 9 params */

#endif
	

#ifndef EXTL_COMPILER_IS_BORLAND
	EXTL_MUST_NOT_BE_CV_FUNC_PTR(int);
	EXTL_MUST_NOT_BE_CV_FUNC_PTR(int &);
	EXTL_MUST_NOT_BE_CV_FUNC_PTR(int *);
	EXTL_MUST_NOT_BE_CV_FUNC_PTR(int [10]);
	EXTL_MUST_NOT_BE_CV_FUNC_PTR(void *);
	EXTL_MUST_NOT_BE_CV_FUNC_PTR(void);
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
