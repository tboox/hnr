/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.06.26					
 * Updated:		08.06.26	
 *
 * Brief: suffix configuration
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WIN_CONFIG_SUFFIX_H
#define EXTL_PLATFORM_WIN_CONFIG_SUFFIX_H

/* ///////////////////////////////////////////////////////////////////////
 * The conversion between BOOL and bool
 */
#ifdef __cplusplus
/* ///////////////////////////////////////////////////////////////////////
 * extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE 

/// BOOL to bool
inline bool BOOL2bool(BOOL bVal)
{
    return bVal != FALSE;
}
/// bool to BOOL
inline BOOL bool2BOOL(bool bVal)
{
    return bVal != false;
}
/* ///////////////////////////////////////////////////////////////////////
 * extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE 
/* //////////////////////////////////////////////////////////////////// */
#else
#	define BOOL2bool(bVal)            (bool)((bVal) != FALSE))
#	define bool2BOOL(bVal)            (BOOL)((bVal) != false))
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
#endif /* EXTL_PLATFORM_WIN_CONFIG_SUFFIX_H */
/* //////////////////////////////////////////////////////////////////// */
