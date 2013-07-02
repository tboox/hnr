/* ///////////////////////////////////////////////////////////////////////
 * File:		sub_config.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Platform Sub-Library Configuration
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_CONFIG_SUB_H
#define EXTL_PLATFORM_CONFIG_SUB_H

#ifndef EXTL_PLATFORM_CONFIG_H
#	error This file must be included of extl\platform\config\config.h
#endif

#ifndef EXTL_CONFIG_SUFFIX_H
#	error This file must be included of extl\config\suffix.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */

/* The Error Library */
#include "../error/config/config.h"

/* The Synchronization Library */
#include "../synch/config/config.h"

/* ///////////////////////////////////////////////////////////////////////
 * The Windows/Unix Library
 */
#if defined(EXTL_PLATFORM_IS_UNIX)
#	include "../unix/config/config.h"
#elif defined(EXTL_PLATFORM_IS_WINDOWS)
#	include "../windows/config/config.h"
#endif


/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_CONFIG_SUB_H */
/* //////////////////////////////////////////////////////////////////// */
