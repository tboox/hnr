/* ///////////////////////////////////////////////////////////////////////
 * File:		namespace.h		
 *
 * Created:		09.02.05					
 * Updated:		09.02.28	
 *
 * Brief:		The Media TS Library Namespace
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MEDIA_TS_CONFIG_NAMESPACE_H
#define EXTL_MEDIA_TS_CONFIG_NAMESPACE_H

#ifndef EXTL_MEDIA_TS_CONFIG_H
#	error This file must be included of extl\media\ts\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ts namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_TS_BEGIN_NAMESPACE		namespace ts{
#	define EXTL_TS_END_NAMESPACE		}
#else
#	define EXTL_TS_BEGIN_NAMESPACE	
#	define EXTL_TS_END_NAMESPACE		
#endif

/* ts::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_TS(x)						ts::x
#else 
#	define EXTL_NS_TS(x)						x
#endif

/* ::extl::media::ts begin */
#define EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE			\
					EXTL_BEGIN_NAMESPACE 			\
					EXTL_MEDIA_BEGIN_NAMESPACE		\
					EXTL_TS_BEGIN_NAMESPACE		


/* ::extl::media::ts end */
#define EXTL_MEDIA_TS_END_WHOLE_NAMESPACE			\
					EXTL_TS_END_NAMESPACE			\
					EXTL_MEDIA_END_NAMESPACE		\
					EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_CONFIG_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */
