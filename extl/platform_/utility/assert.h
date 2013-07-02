/* ///////////////////////////////////////////////////////////////////////
 * File:		assert.h		
 *
 * Created:		08.02.02				
 * Updated:		08.11.09
 *
 * Brief:		Assertion
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_UTILITY_ASSERT_H
#define EXTL_PLATFORM_UTILITY_ASSERT_H

/*!\file assert.h
 * \brief assertion
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h" 
#include "../../type/typedef.h"

#if defined(EXTL_PLATFORM_IS_UNIX)
#	include "../unix/utility/assert_failed.h"
#elif defined(EXTL_PLATFORM_IS_WINDOWS)
#	include "../windows/utility/assert_failed.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

#ifndef EXTL_ASSERT_DISABLE
#	define EXTL_ASSERT(expr)	((expr)? ((void)0): \
									EXTL_NS(EXTL_NS_PLATFORM(g_afp)) \
										(EXTL_LINENUM, #expr, EXTL_CURRENT_FUNCTION, EXTL_FILENAME))

#	define EXTL_MESSAGE_ASSERT(expr, msg)		EXTL_ASSERT(expr && msg)
#	define EXTL_SET_ASSERT_FAILED_PROC(func)	EXTL_NS(EXTL_NS_PLATFORM(set_assertion_failed_proc))(func)
#else
#	define EXTL_ASSERT(expr)	
#	define EXTL_MESSAGE_ASSERT(expr, msg)
#	define EXTL_SET_ASSERT_FAILED_PROC(func)	
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::platform namespace
 */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE 

/* The assertion-failed handle function */
typedef void (*xtl_afp)	(	e_uint_t const line 
						,	e_char_t const *expr 
						,	e_char_t const *func 
						,	e_char_t const *file);

static xtl_afp	g_afp = EXTL_NS_PLATFORM_SPEC(assertion_failed);

/* Sets the assertion-failed handle function */
EXTL_INLINE xtl_afp set_assertion_failed_proc(xtl_afp afp)
{
	xtl_afp old_afp = g_afp;
	g_afp = (afp == NULL)? EXTL_NS_PLATFORM_SPEC(assertion_failed) : afp;
	return old_afp;
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::platform namespace
 */
EXTL_PLATFORM_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_UTILITY_ASSERT_H */
/* //////////////////////////////////////////////////////////////////// */
