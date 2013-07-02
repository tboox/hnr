/* ///////////////////////////////////////////////////////////////////////
 * File:		platorm.h		
 *
 * Created:		08.02.02				
 * Updated:		08.05.05
 *
 * Brief: Extensible platform library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_H
#define EXTL_PLATFORM_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "config/config.h"

#if defined(EXTL_PLATFORM_IS_WIN)
#	include "../win/win.h"
#elif defined(EXTL_PLATFORM_IS_UNIX)
#	include "../unix/unix.h"
#else
#	error Unknown Platform.
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_H */
/* //////////////////////////////////////////////////////////////////// */
