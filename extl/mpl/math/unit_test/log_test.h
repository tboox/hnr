/* ///////////////////////////////////////////////////////////////////////
 * File:		log_test.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.09
 *
 * Brief: Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_MATH_LOG_TEST_H
#define EXTL_MPL_MATH_LOG_TEST_H

#ifndef EXTL_MPL_MATH_LOG_H
#	error This file must be included of log.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void log_test()
{
	EXTL_STATIC_ASSERT((log<2, 4>::value == 2));
	EXTL_STATIC_ASSERT((log<3, 3>::value == 1));
	EXTL_STATIC_ASSERT((log<3, 27>::value == 3));
	EXTL_STATIC_ASSERT((log<2, 1024>::value == 10));
	EXTL_STATIC_ASSERT((log<2, 1>::value == 0));

	EXTL_STATIC_ASSERT((log_2<4>::value == 2));
	EXTL_STATIC_ASSERT((log_2<1024>::value == 10));
	EXTL_STATIC_ASSERT((log_10<1000>::value == 3));
}


/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_MATH_LOG_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
