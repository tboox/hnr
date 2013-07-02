/* ///////////////////////////////////////////////////////////////////////
 * File:		is_void_test.h		
 *
 * Created:		08.02.02			
 * Updated:		08.07.13
 *
 * Brief: is_void unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_VOID_H
#	error This file must be included of is_void.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void is_void_test()
{
	EXTL_MUST_BE_CV_VOID(void);
}
/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
