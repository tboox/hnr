/* ///////////////////////////////////////////////////////////////////////
 * File:		platorm.h		
 *
 * Created:		08.06.26			
 * Updated:		08.06.26
 *
 * Brief: Extensible platform library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_NAMESPACE_H
#define EXTL_PLATFORM_NAMESPACE_H

/* ///////////////////////////////////////////////////////////////////////
 * Namespace
 */
#ifndef	EXTL_NO_NAMESPACE

/* extl::platform */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE	

/* using namespace extl::platform::win/unix; */
#if defined(EXTL_PLATFORM_IS_UNIX)
	EXTL_NS_USING_NAMESPACE(unix)
#elif defined(EXTL_PLATFORM_IS_WIN)
	EXTL_NS_USING_NAMESPACE(win)
#endif

/* extl::platform */
EXTL_PLATFORM_END_WHOLE_NAMESPACE	

/* platform_extl */
namespace platform_extl = extl::platform;

#endif /* EXTL_NO_NAMESPACE */

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */
