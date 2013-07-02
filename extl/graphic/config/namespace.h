/* ///////////////////////////////////////////////////////////////////////
 * File:		namespace.h		
 *
 * Created:		08.12.31				
 * Updated:		08.12.31	
 *
 * Brief:		The Graphic Library Namespace
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_GRAPHIC_CONFIG_NAMESPACE_H
#define EXTL_GRAPHIC_CONFIG_NAMESPACE_H

#ifndef EXTL_GRAPHIC_CONFIG_H
#	error This file must be included of extl\graphic\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * graphic namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_GRAPHIC_BEGIN_NAMESPACE				namespace graphic{
#	define EXTL_GRAPHIC_END_NAMESPACE				}
#else
#	define EXTL_GRAPHIC_BEGIN_NAMESPACE	
#	define EXTL_GRAPHIC_END_NAMESPACE		
#endif

/* graphic::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_GRAPHIC(x)						graphic::x
#else 
#	define EXTL_NS_GRAPHIC(x)						x
#endif

/* ::extl::graphic begin */
#define EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE			\
					EXTL_BEGIN_NAMESPACE 			\
					EXTL_GRAPHIC_BEGIN_NAMESPACE


/* ::extl::graphic end */
#define EXTL_GRAPHIC_END_WHOLE_NAMESPACE			\
					EXTL_GRAPHIC_END_NAMESPACE		\
					EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_GRAPHIC_CONFIG_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */
