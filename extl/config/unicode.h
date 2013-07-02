/* ///////////////////////////////////////////////////////////////////////
 * File:		unicode.h		
 *
 * Created:		08.02.02					
 * Updated:		08.04.14	
 *
 * Brief: Unicode character-set
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONFIG_UNICODE_H
#define EXTL_CONFIG_UNICODE_H

#ifndef  EXTL_CONFIG_H
#	error This file must be included of config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unicode character-set
 */ 
#if defined(EXTL_UNICODE) || defined(UNICODE) || defined(_UNICODE)

#	ifndef EXTL_UNICODE
#		define EXTL_UNICODE
#	endif

#	ifndef UNICODE
#		define UNICODE
#	endif

#	ifndef _UNICODE
#		define _UNICODE
#	endif

#endif

#include "stdio.h"
#include "tchar.h"

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_UNICODE_H */
/* //////////////////////////////////////////////////////////////////// */
