/* ///////////////////////////////////////////////////////////////////////
 * File:		namespace.h
 *
 * Created:		08.06.26
 * Updated:		08.11.09
 *
 * Brief: Windows library namespace
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WINDOWS_NAMESPACE_H
#define EXTL_PLATFORM_WINDOWS_NAMESPACE_H

#ifndef EXTL_PLATFORM_WINDOWS_CONFIG_H
#	error This file must be included of extl\platform\windows\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::windows namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_WINDOWS_BEGIN_NAMESPACE				namespace wxtl{
#	define EXTL_WINDOWS_END_NAMESPACE				}
#else
#	define EXTL_WINDOWS_BEGIN_NAMESPACE
#	define EXTL_WINDOWS_END_NAMESPACE
#endif

/* windows::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_WINDOWS(x)						wxtl::x
#else
#	define EXTL_NS_WINDOWS(x)						x
#endif

/* ::extl::platform::windows namespace begin */
#define EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE			\
					EXTL_BEGIN_NAMESPACE			\
					EXTL_PLATFORM_BEGIN_NAMESPACE	\
					EXTL_WINDOWS_BEGIN_NAMESPACE


/* ::extl::platform::windows namespace end */
#define EXTL_WINDOWS_END_WHOLE_NAMESPACE			\
					EXTL_WINDOWS_END_NAMESPACE		\
					EXTL_PLATFORM_END_NAMESPACE		\
					EXTL_END_NAMESPACE

/* platform specific namespace */
#define EXTL_NS_PLATFORM_SPEC(x)					EXTL_NS_WINDOWS(x)
/* platform specific using */
#define EXTL_NS_USING_PLATFORM_SPEC(x)				EXTL_NS_USING(EXTL_NS_WINDOWS(x))
/* platform specific using namepsace */
#define EXTL_NS_USING_PLATFORM_NAMESPACE_SPEC(x)	EXTL_NS_USING_NAMESPACE(EXTL_NS_WINDOWS(x))

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */

