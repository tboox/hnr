/* ///////////////////////////////////////////////////////////////////////
 * File:		if_test.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_IF_TEST_H
#define EXTL_MPL_IF_TEST_H

#ifndef EXTL_MPL_IF_H
#	error This file must be included of if_.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void if_test()
{
	typedef if_<1, e_int_t, void >::type if_test_int;
	typedef if_<0, e_int_t, void >::type if_test_void;
	EXTL_MUST_BE_INT(if_test_int);
	EXTL_MUST_BE_VOID(if_test_void);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_IF_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
