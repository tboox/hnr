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

#ifndef EXTL_PLATFORM_WINDOWS_CONFIG_SUFFIX_H
#define EXTL_PLATFORM_WINDOWS_CONFIG_SUFFIX_H

#ifndef EXTL_PLATFORM_WINDOWS_CONFIG_H
#	error This file must be included of extl\platform\windows\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * The conversion between BOOL and bool
 */
#ifdef __cplusplus
/* ///////////////////////////////////////////////////////////////////////
 * extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE 

/// BOOL to bool
inline bool BOOL2bool(BOOL b)
{
    return b != FALSE;
}
/// bool to BOOL
inline BOOL bool2BOOL(bool b)
{
    return b != false;
}
/* ///////////////////////////////////////////////////////////////////////
 * extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE 
/* //////////////////////////////////////////////////////////////////// */
#else
#	define BOOL2bool(b)			(bool)((b) != FALSE))
#	define bool2BOOL(b)			(BOOL)((b) != false))
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
#endif /* EXTL_PLATFORM_WINDOWS_CONFIG_SUFFIX_H */
/* //////////////////////////////////////////////////////////////////// */
