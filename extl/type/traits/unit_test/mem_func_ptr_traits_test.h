/* ///////////////////////////////////////////////////////////////////////
 * File:		mem_func_ptr_traits_test.h		
 *
 * Created:		08.07.16					
 * Updated:		08.07.16
 *
 * Brief: mem_func_ptr_traits unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_H
#	error This file must be included of mem_func_ptr_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct mfpt_containter{};
EXTL_INLINE void mem_func_ptr_traits_test()
{
	typedef mem_func_ptr_traits<int (mfpt_containter::*)(int, void*)> mem_func_ptr_traits_type;
	mem_func_ptr_traits_type::param1_type p1 = 10;
	mem_func_ptr_traits_type::param2_type p2 = NULL;
	EXTL_STATIC_ASSERT(mem_func_ptr_traits_type::is_cdecl);

#ifdef EXTL_ELLIPSIS_IN_FUNC_TESTING_SUPPORT
	typedef mem_func_ptr_traits<int (mfpt_containter::*)(int, void* ...)> mem_func_ptr_traits_type2;
	mem_func_ptr_traits_type2::param1_type p3 = 10;
	mem_func_ptr_traits_type2::param2_type p4 = NULL;
	EXTL_STATIC_ASSERT(mem_func_ptr_traits_type2::is_cdecl);
	EXTL_STATIC_ASSERT(mem_func_ptr_traits_type2::has_ellipsis);
#endif
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
