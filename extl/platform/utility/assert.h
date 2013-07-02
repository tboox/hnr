/* ///////////////////////////////////////////////////////////////////////
 * File:		assert.h		
 *
 * Created:		08.02.02				
 * Updated:		08.05.05
 *
 * Brief: platform assertion
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_UTILITY_ASSERT_H
#define EXTL_PLATFORM_UTILITY_ASSERT_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../../config/config.h" 
#include "../../type/typedef.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

#ifndef EXTL_ASSERT_DISABLE
#	define EXTL_ASSERT(expr)	((expr)? ((void)0): \
									EXTL_NS(EXTL_NS_PLATFORM(g_assertion_failed_proc)) \
										(EXTL_LINENUM, #expr, EXTL_CURRENT_FUNCTION, EXTL_FILENAME))

#	define EXTL_MESSAGE_ASSERT(expr, msg)		EXTL_ASSERT(expr && msg)
#	define EXTL_SET_ASSERT_FAILED_PROC(func)	EXTL_NS(EXTL_NS_PLATFORM(set_assertion_failed_proc))(func)
#else
#	define EXTL_ASSERT(expr)	
#	define EXTL_MESSAGE_ASSERT(expr, msg)
#	define EXTL_SET_ASSERT_FAILED_PROC(func)	
#endif

/* The maximum size of the assertion-failed message text */
#define EXTL_ASSERT_MSG_SIZE_MAX	256

/* Includes */
#if defined(EXTL_PLATFORM_IS_UNIX)
#	include "../../unix/utility/assert_failed.h"
#elif defined(EXTL_PLATFORM_IS_WIN)
#	include "../../win/utility/assert_failed.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::platform namespace
 */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE 

/* using extl::platform::::win/unix::assertion_failed; */
#if defined(EXTL_PLATFORM_IS_UNIX)
EXTL_NS_USING(EXTL_NS(EXTL_NS_PLATFORM(EXTL_NS_UNIX(assertion_failed))))
#elif defined(EXTL_PLATFORM_IS_WIN)
EXTL_NS_USING(EXTL_NS(EXTL_NS_PLATFORM(EXTL_NS_WIN(assertion_failed))))
#endif

/* The assertion-failed handle function */
typedef void (*EXTL_ASSERTION_FAILED_PROC)(e_uint_t const_ref nLine, 
											e_char_t const *pszExpr, 
											e_char_t const *pszFunc, 
											e_char_t const *pszFile);

static EXTL_ASSERTION_FAILED_PROC	g_assertion_failed_proc = assertion_failed;

/* Sets the assertion-failed handle function */
EXTL_INLINE EXTL_ASSERTION_FAILED_PROC set_assertion_failed_proc(EXTL_ASSERTION_FAILED_PROC passertion_failedProc)
{
	EXTL_ASSERTION_FAILED_PROC pOldassertion_failedProc = g_assertion_failed_proc;
	g_assertion_failed_proc = (passertion_failedProc == NULL)? assertion_failed : passertion_failedProc;
	return pOldassertion_failedProc;
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::platform namespace
 */
EXTL_PLATFORM_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_UTILITY_ASSERT_H */
/* //////////////////////////////////////////////////////////////////// */
