/* ///////////////////////////////////////////////////////////////////////
 * File:		platorm.h		
 *
 * Created:		08.06.26			
 * Updated:		08.11.09
 *
 * Brief: Extensible platform library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_NAMESPACE_H
#define EXTL_PLATFORM_NAMESPACE_H

#ifndef EXTL_PLATFORM_CONFIG_H
#	error This file must be included of extl\platform\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * platform namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_PLATFORM_BEGIN_NAMESPACE		namespace platform{
#	define EXTL_PLATFORM_END_NAMESPACE			}
#else
#	define EXTL_PLATFORM_BEGIN_NAMESPACE	
#	define EXTL_PLATFORM_END_NAMESPACE		
#endif

/* platform::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_PLATFORM(x)					platform::x
#else 
#	define EXTL_NS_PLATFORM(x)					x
#endif

/* ::extl::platform namespace begin */
#define EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE	\
					EXTL_BEGIN_NAMESPACE	\
					EXTL_PLATFORM_BEGIN_NAMESPACE	


/* ::extl::platform namespace end */
#define EXTL_PLATFORM_END_WHOLE_NAMESPACE	\
					EXTL_PLATFORM_END_NAMESPACE	\
					EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */
