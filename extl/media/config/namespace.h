/* ///////////////////////////////////////////////////////////////////////
 * File:		namespace.h		
 *
 * Created:		09.02.05					
 * Updated:		09.02.05	
 *
 * Brief:		The Media Library Namespace
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MEDIA_CONFIG_NAMESPACE_H
#define EXTL_MEDIA_CONFIG_NAMESPACE_H

#ifndef EXTL_MEDIA_CONFIG_H
#	error This file must be included of extl\media\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * media namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_MEDIA_BEGIN_NAMESPACE				namespace media{
#	define EXTL_MEDIA_END_NAMESPACE				}
#else
#	define EXTL_MEDIA_BEGIN_NAMESPACE	
#	define EXTL_MEDIA_END_NAMESPACE		
#endif

/* media::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_MEDIA(x)						media::x
#else 
#	define EXTL_NS_MEDIA(x)						x
#endif

/* ::extl::media begin */
#define EXTL_MEDIA_BEGIN_WHOLE_NAMESPACE			\
					EXTL_BEGIN_NAMESPACE 		\
					EXTL_MEDIA_BEGIN_NAMESPACE


/* ::extl::media end */
#define EXTL_MEDIA_END_WHOLE_NAMESPACE			\
					EXTL_MEDIA_END_NAMESPACE		\
					EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_CONFIG_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */
