/* ///////////////////////////////////////////////////////////////////////
 * File:		assert_failed.h
 *
 * Created:		08.02.07
 * Updated:		09.01.15
 *
 * Brief:		the assertion_failed handle function
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_UNIX_UTILITY_ASSERT_FAILED_H
#define EXTL_PLATFORM_UNIX_UTILITY_ASSERT_FAILED_H

/*!\file assert_failed.h
 * \brief the assertion_failed handle function
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
/* The maximum size of the assertion-failed message text */
#define EXTL_ASSERT_MSG_SIZE_MAX	256

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::unix namespace
 */
EXTL_UNIX_BEGIN_WHOLE_NAMESPACE

/*!\brief assertion_failed handle function
 * \ingroup extl_group_utility
 */
#ifdef EXTL_INLINE_ASM_IN_INLINE_SUPPORT
EXTL_INLINE
#else
static
#endif
void assertion_failed(e_uint_t const line, e_char_t const *expr, e_char_t const *func, e_char_t const *file)
{

}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::unix namespace
 */
EXTL_UNIX_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_PLATFORM_UNIX_UTILITY_ASSERT_FAILED_H */
/* //////////////////////////////////////////////////////////////////// */


