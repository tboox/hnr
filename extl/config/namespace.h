/* ///////////////////////////////////////////////////////////////////////
 * File:		namespace.h
 *
 * Created:		08.02.02
 * Updated:		08.04.15
 *
 * Brief: namespace config
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONFIG_NAMESPACE_H
#define EXTL_CONFIG_NAMESPACE_H

#ifndef EXTL_CONFIG_SUFFIX_H
#	error This file must be included of extl\config\suffix.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * No namespace
 */
#if !defined(__cplusplus)
#	if !defined(EXTL_NO_NAMESPACE)
#		define EXTL_NO_NAMESPACE
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_BEGIN_NAMESPACE					namespace extl{
#	define EXTL_END_NAMESPACE					}
#else
#	define EXTL_BEGIN_NAMESPACE
#	define EXTL_END_NAMESPACE
#endif

/*  using ::x; */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS(x)							::extl::x
#	define EXTL_NS_USING(x)						using	x;
#	define EXTL_NS_USING_NAMESPACE(x)			using namespace x;
#else
#	ifdef __cplusplus
#		define EXTL_NS(x)						::x
#	else
#		define EXTL_NS(x)						x
#	endif
#	define EXTL_NS_USING(x)
#	define EXTL_NS_USING_NAMESPACE(x)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * detail namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_DETAIL_BEGIN_NAMESPACE			namespace detail{
#	define EXTL_DETAIL_END_NAMESPACE			}
#else
#	define EXTL_DETAIL_BEGIN_NAMESPACE
#	define EXTL_DETAIL_END_NAMESPACE
#endif

/* detail::x; */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_DETAIL(x)					detail::x
#else
#	define EXTL_NS_DETAIL(x)					x
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Anonymous namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_ANONYMOUS_BEGIN_NAMESPACE		namespace {
#	define EXTL_ANONYMOUS_END_NAMESPACE			}
#else
#	define EXTL_ANONYMOUS_BEGIN_NAMESPACE
#	define EXTL_ANONYMOUS_END_NAMESPACE
#endif

/* ///////////////////////////////////////////////////////////////////////
 *  test namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_TEST_BEGIN_NAMESPACE					namespace test{
#	define EXTL_TEST_END_NAMESPACE						}
#	define EXTL_TEST_NAME_BEGIN_NAMESPACE(name)			namespace test_##name{
#	define EXTL_TEST_NAME_END_NAMESPACE(name)			}
#else
#	define EXTL_TEST_BEGIN_NAMESPACE
#	define EXTL_TEST_END_NAMESPACE
#	define EXTL_TEST_NAME_BEGIN_NAMESPACE(name)
#	define EXTL_TEST_NAME_END_NAMESPACE(name)
#endif

/* test::x; */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_NS_TEST(x)					test::x
#	define EXTL_NS_TEST_NAME(name)			test_##name::x
#else
#	define EXTL_NS_TEST(x)					x
#	define EXTL_NS_TEST_NAME(name)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * std namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_STD_BEGIN_NAMESPACE				namespace std{
#	define EXTL_STD_END_NAMESPACE				}
#else
#	define EXTL_STD_BEGIN_NAMESPACE
#	define EXTL_STD_END_NAMESPACE
#endif

/* ::std::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_STD(x)						::std::x
#else
#	define EXTL_NS_STD(x)						x
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Global namespace
 */
#if defined(__cplusplus)
#	define EXTL_NS_GLOBAL(x)					::x
#else
#	define EXTL_NS_GLOBAL(x)					x
#endif

#ifndef EXTL_NEW_PLATFORM_ENABLE
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

/* ///////////////////////////////////////////////////////////////////////
 * ::win namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_WIN_BEGIN_NAMESPACE				namespace win{
#	define EXTL_WIN_END_NAMESPACE				}
#else
#	define EXTL_WIN_BEGIN_NAMESPACE
#	define EXTL_WIN_END_NAMESPACE
#endif

/* win::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_WIN(x)						win::x
#else
#	define EXTL_NS_WIN(x)						x
#endif

/* ::extl::platform::win namespace begin */
#define EXTL_WIN_BEGIN_WHOLE_NAMESPACE	\
					EXTL_BEGIN_NAMESPACE	\
					EXTL_PLATFORM_BEGIN_NAMESPACE	\
					EXTL_WIN_BEGIN_NAMESPACE


/* ::extl::platform::win namespace end */
#define EXTL_WIN_END_WHOLE_NAMESPACE	\
					EXTL_WIN_END_NAMESPACE \
					EXTL_PLATFORM_END_NAMESPACE	\
					EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * unix namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_UNIX_BEGIN_NAMESPACE			namespace unix{
#	define EXTL_UNIX_END_NAMESPACE				}
#else
#	define EXTL_UNIX_BEGIN_NAMESPACE
#	define EXTL_UNIX_END_NAMESPACE
#endif

/* unix::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_UNIX(x)						unix::x
#else
#	define EXTL_NS_UNIX(x)						x
#endif

/* ::extl::platform::unix namespace begin */
#define EXTL_UNIX_BEGIN_WHOLE_NAMESPACE	\
					EXTL_BEGIN_NAMESPACE	\
					EXTL_PLATFORM_BEGIN_NAMESPACE	\
					EXTL_UNIX_BEGIN_NAMESPACE


/* ::extl::platform::unix namespace end */
#define EXTL_UNIX_END_WHOLE_NAMESPACE	\
					EXTL_UNIX_END_NAMESPACE \
					EXTL_PLATFORM_END_NAMESPACE	\
					EXTL_END_NAMESPACE

#endif /* EXTL_NEW_PLATFORM_ENABLE */
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */
