/* ///////////////////////////////////////////////////////////////////////
 * File:		static_assert.h		
 *
 * Created:		08.02.02				
 * Updated:		08.05.05	
 *
 * Brief: static assertion
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_STATIC_MESSAGE_ASSERT_H
#define EXTL_UTILITY_STATIC_MESSAGE_ASSERT_H

/*!\file static_assert.h
 * \brief static assertion
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "static_assert.h" 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * static assertion
 */
#ifdef EXTL_0x_STATIC_MESSAGE_ASSERT_SUPPORT // c++0x
#	define EXTL_STATIC_MESSAGE_ASSERT(expr, msg)		static_assert(expr, msg)
#else 
#	define EXTL_STATIC_MESSAGE_ASSERT(expr, msg)		EXTL_STATIC_ASSERT(expr)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_STATIC_MESSAGE_ASSERT_H */
/* //////////////////////////////////////////////////////////////////// */
