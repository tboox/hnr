/* ///////////////////////////////////////////////////////////////////////
 * File:		func_ptr_traits_test.h		
 *
 * Created:		08.07.16					
 * Updated:		08.07.16
 *
 * Brief: func_ptr_traits unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_H
#	error This file must be included of func_ptr_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void func_ptr_traits_test()
{
	typedef func_ptr_traits<int (*)(int, void*)> func_ptr_traits_type;
	func_ptr_traits_type::param1_type p1 = 10;
	func_ptr_traits_type::param2_type p2 = NULL;
	EXTL_STATIC_ASSERT(func_ptr_traits_type::is_cdecl);

#ifdef EXTL_ELLIPSIS_IN_FUNC_TESTING_SUPPORT
	typedef func_ptr_traits<int (*)(int, void* ...)> func_ptr_traits_type2;
	func_ptr_traits_type2::param1_type p3 = 10;
	func_ptr_traits_type2::param2_type p4 = NULL;
	EXTL_STATIC_ASSERT(func_ptr_traits_type2::is_cdecl);
	EXTL_STATIC_ASSERT(func_ptr_traits_type2::has_ellipsis);
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
