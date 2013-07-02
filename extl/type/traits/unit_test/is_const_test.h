/* ///////////////////////////////////////////////////////////////////////
 * File:		is_const_test.h		
 *
 * Created:		08.02.02					
 * Updated:		08.07.09	
 *
 * Brief: is_const unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CONST_H
#	error This file must be included of is_const.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_const_test()
{
	EXTL_MUST_BE_CONST(int const);
	EXTL_MUST_BE_CONST(int *const);
	EXTL_MUST_BE_CONST(int const*const);
	EXTL_MUST_BE_CONST(int const volatile);
	EXTL_MUST_BE_CONST(int *const volatile);
	EXTL_MUST_BE_CONST(int (*const)());

	EXTL_MUST_BE_CONST(void *const);
	EXTL_MUST_BE_CONST(void const * const);
	EXTL_MUST_BE_CONST(void *const volatile);
	EXTL_MUST_BE_CONST(void (*const)());

	EXTL_MUST_BE_CONST(int const[10]);
	EXTL_MUST_BE_CONST(int const volatile[10]);
	
#ifdef EXTL_CV_VOID_SPEC_SUPPORT
	EXTL_MUST_BE_CONST(void const);
	EXTL_MUST_BE_CONST(void const volatile);
	
#else
	EXTL_MUST_NOT_BE_CONST(void const);
	EXTL_MUST_NOT_BE_CONST(void const volatile);
#endif

#if (defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER > 1310))
	struct const_struct;
	EXTL_MUST_BE_CONST(int const_struct::*const);
	EXTL_MUST_BE_CONST(int (const_struct::* const)());
#endif
	
	EXTL_MUST_NOT_BE_CONST(int const&);
	EXTL_MUST_NOT_BE_CONST(int const volatile&);
	EXTL_MUST_NOT_BE_CONST(int const*); // note: non-const pointer 
	EXTL_MUST_NOT_BE_CONST(int const volatile*);
	EXTL_MUST_NOT_BE_CONST(void const volatile*);
	EXTL_MUST_NOT_BE_CONST(void const*);

	EXTL_MUST_NOT_BE_CONST(int *);
	EXTL_MUST_NOT_BE_CONST(int &);

	EXTL_MUST_NOT_BE_CONST(volatile int *);
	EXTL_MUST_NOT_BE_CONST(volatile int &);

#ifndef EXTL_COMPILER_IS_DMC
	/* EXTL_MUST_BE_CONST(void const); 
	EXTL_MUST_BE_CONST(void const volatile); cannot be used at same time */
	EXTL_MUST_NOT_BE_CONST(volatile void);
	EXTL_MUST_NOT_BE_CONST(void);

	/* EXTL_MUST_BE_CONST(int const[10]);
	EXTL_MUST_BE_CONST(int const volatile[10]); cannot be used at same time */
	EXTL_MUST_NOT_BE_CONST(int [10]);
	EXTL_MUST_NOT_BE_CONST(volatile int [10]);
#endif
	
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
