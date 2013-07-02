/* ///////////////////////////////////////////////////////////////////////
 * File:		call_traits_test.h		
 *
 * Created:		08.07.21					
 * Updated:		08.07.21	
 *
 * Brief: call_traits unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_TYPE_TRAITS_CALL_TRAITS_H
#	error This file must be included of call_traits.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void call_traits_test_func1(int&){}
EXTL_INLINE void call_traits_test_func2(int){}
EXTL_INLINE void call_traits_test_func3(call_traits<int&>::param_type a)
{ 
	call_traits_test_func1(a);
}; 
EXTL_INLINE void call_traits_test_func4(call_traits<int>::param_type a)
{ 
	call_traits_test_func2(a);
}; 

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

