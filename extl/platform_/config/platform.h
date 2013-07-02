/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.02.02				
 * Updated:		08.11.09	
 *
 * Brief:		platform detecting
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_CONFIG_PLATFORM_H
#define EXTL_PLATFORM_CONFIG_PLATFORM_H

#ifndef EXTL_PLATFORM_CONFIG_H
#	error This file must be included of extl\platform\config\config.h
#endif

// Unix platform  
#if defined(unix) || \
    defined(UNIX) || \
    defined(__unix__) || \
    defined(__unix)
#	define EXTL_PLATFORM_IS_UNIX
// Windows platform 
#elif defined(WIN32) || \
      defined(_WIN32) || \
      defined(__WIN32__)
#	define EXTL_PLATFORM_IS_WINDOWS
#else 
#	error Unknown Operating system.
#endif 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_CONFIG_PLATFORM_H */
/* //////////////////////////////////////////////////////////////////// */
