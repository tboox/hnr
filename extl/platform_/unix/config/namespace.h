/* ///////////////////////////////////////////////////////////////////////
 * File:		namespace.h
 *
 * Created:		08.06.26
 * Updated:		08.11.09
 *
 * Brief: Unix library namespace
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_UNIX_NAMESPACE_H
#define EXTL_PLATFORM_UNIX_NAMESPACE_H

#ifndef EXTL_PLATFORM_UNIX_CONFIG_H
#	error This file must be included of extl\platform\unix\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unix namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_UNIX_BEGIN_NAMESPACE			namespace uxtl{
#	define EXTL_UNIX_END_NAMESPACE				}
#else
#	define EXTL_UNIX_BEGIN_NAMESPACE
#	define EXTL_UNIX_END_NAMESPACE
#endif

/* unix::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_UNIX(x)						uxtl::x
#else
#	define EXTL_NS_UNIX(x)						x
#endif

/* ::extl::platform::unix namespace begin */
#define EXTL_UNIX_BEGIN_WHOLE_NAMESPACE				\
					EXTL_BEGIN_NAMESPACE			\
					EXTL_PLATFORM_BEGIN_NAMESPACE	\
					EXTL_UNIX_BEGIN_NAMESPACE


/* ::extl::platform::unix namespace end */
#define EXTL_UNIX_END_WHOLE_NAMESPACE				\
					EXTL_UNIX_END_NAMESPACE			\
					EXTL_PLATFORM_END_NAMESPACE		\
					EXTL_END_NAMESPACE


/* platform specific namespace */
#define EXTL_NS_PLATFORM_SPEC(x)					EXTL_NS_UNIX(x)
/* platform specific using */
#define EXTL_NS_USING_PLATFORM_SPEC(x)				EXTL_NS_USING(EXTL_NS_UNIX(x))
/* platform specific using namepsace */
#define EXTL_NS_USING_PLATFORM_NAMESPACE_SPEC(x)	EXTL_NS_USING_NAMESPACE(EXTL_NS_UNIX(x))

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_UNIX_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */

