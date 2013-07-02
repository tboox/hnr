/* ///////////////////////////////////////////////////////////////////////
 * File:		is_volatile_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: is_volatile unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_VOLATILE_H
#	error This file must be included of is_volatile.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_volatile_test()
{
	EXTL_MUST_BE_VOLATILE(int volatile);
	EXTL_MUST_BE_VOLATILE(int *volatile);
	EXTL_MUST_BE_VOLATILE(int volatile*volatile);
	EXTL_MUST_BE_VOLATILE(int const volatile);
	EXTL_MUST_BE_VOLATILE(int *const volatile);
	EXTL_MUST_BE_VOLATILE(int (*volatile)());

	EXTL_MUST_BE_VOLATILE(void *volatile);
	EXTL_MUST_BE_VOLATILE(void volatile * volatile);
	EXTL_MUST_BE_VOLATILE(void *const volatile);
	EXTL_MUST_BE_VOLATILE(void (*volatile)());

	EXTL_MUST_BE_VOLATILE(int volatile[10]);
	EXTL_MUST_BE_VOLATILE(int const volatile[10]);
	
#ifdef EXTL_CV_VOID_SPEC_SUPPORT
	EXTL_MUST_BE_VOLATILE(void volatile);
	EXTL_MUST_BE_VOLATILE(void const volatile);
	
#else
	EXTL_MUST_NOT_BE_VOLATILE(void volatile);
	EXTL_MUST_NOT_BE_VOLATILE(void const volatile);
#endif

#if (defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER > 1310))
	struct volatile_struct;
	EXTL_MUST_BE_VOLATILE(int volatile_struct::*volatile);
	EXTL_MUST_BE_VOLATILE(int (volatile_struct::* volatile)());
#endif
	
	EXTL_MUST_NOT_BE_VOLATILE(int volatile&);
	EXTL_MUST_NOT_BE_VOLATILE(int const volatile&);
	EXTL_MUST_NOT_BE_VOLATILE(int volatile*); 
	EXTL_MUST_NOT_BE_VOLATILE(int const volatile*);
	EXTL_MUST_NOT_BE_VOLATILE(void const volatile*);
	EXTL_MUST_NOT_BE_VOLATILE(void volatile*);

	EXTL_MUST_NOT_BE_VOLATILE(int *);
	EXTL_MUST_NOT_BE_VOLATILE(int &);

	EXTL_MUST_NOT_BE_VOLATILE(const int *);
	EXTL_MUST_NOT_BE_VOLATILE(const int &);

#ifndef EXTL_COMPILER_IS_DMC
	/*与 EXTL_MUST_BE_VOLATILE(void volatile); 
	EXTL_MUST_BE_VOLATILE(void const volatile); 不能同时使用*/
	EXTL_MUST_NOT_BE_VOLATILE(const void);
	EXTL_MUST_NOT_BE_VOLATILE(void);

	/*与  EXTL_MUST_BE_VOLATILE(int volatile[10]);
	EXTL_MUST_BE_VOLATILE(int const volatile[10]); 不能同时使用*/
	EXTL_MUST_NOT_BE_VOLATILE(int [10]);
	EXTL_MUST_NOT_BE_VOLATILE(const int [10]);
#endif
	
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
