/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.06.26					
 * Updated:		08.11.09
 *
 * Brief: suffix configuration
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_UNIX_CONFIG_SUFFIX_H
#define EXTL_PLATFORM_UNIX_CONFIG_SUFFIX_H

#ifndef EXTL_PLATFORM_UNIX_CONFIG_H
#	error This file must be included of extl\platform\unix\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * The maximum size of path 
 */
#ifdef MAX_PATH
#	define EXTL_MAX_PATH			MAX_PATH
#else
#	define EXTL_MAX_PATH			256
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_UNIX_CONFIG_SUFFIX_H */
/* //////////////////////////////////////////////////////////////////// */
