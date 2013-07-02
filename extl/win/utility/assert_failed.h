/* ///////////////////////////////////////////////////////////////////////
 * File:		assert_failed.h		
 *
 * Created:		08.02.07				
 * Updated:		08.05.05
 *
 * Brief: assertion_failed handle function
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_UTILITY_ASSERT_FAILED_H
#define EXTL_PLATFORM_WIN_UTILITY_ASSERT_FAILED_H

/*!\file assert_failed.h
 * \brief assertion_failed handle function
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../../config/config.h" 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief assertion_failed handle function
 * \ingroup extl_group_utility
 */
#ifdef EXTL_INLINE_ASM_IN_INLINE_SUPPORT
EXTL_INLINE 
#else
static
#endif
void assertion_failed(e_uint_t const_ref nLine, e_char_t const *pszExpr, e_char_t const *pszFunc, e_char_t const *pszFile)
{
	e_char_t szMsg[EXTL_ASSERT_MSG_SIZE_MAX];

	e_a_sprintf(szMsg, "Code:%s\nLine:%d\nFunc:%s\nFile:%s\n\nDo you debug?", 
		pszExpr, nLine, pszFunc, pszFile);

	e_int_t nRet = MessageBoxA(NULL, szMsg, "Assert failure", MB_YESNO);
	if(nRet == IDYES)
	{
#ifdef EXTL_INLINE_ASM_SUPPORT
		__asm int 3
#endif
	}
	else 
	{
		TerminateProcess(GetCurrentProcess(),0);
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_PLATFORM_WIN_UTILITY_ASSERT_FAILED_H */
/* //////////////////////////////////////////////////////////////////// */


