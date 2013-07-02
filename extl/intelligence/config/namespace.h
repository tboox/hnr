/* ///////////////////////////////////////////////////////////////////////
 * File:		namespace.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Intelligence Library Namespace
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_CONFIG_NAMESPACE_H
#define EXTL_INTELLIGENCE_CONFIG_NAMESPACE_H

#ifndef EXTL_INTELLIGENCE_CONFIG_H
#	error This file must be included of extl\intelligence\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * intelligence namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_INTELLIGENCE_BEGIN_NAMESPACE			namespace intelligence{
#	define EXTL_INTELLIGENCE_END_NAMESPACE				}
#else
#	define EXTL_INTELLIGENCE_BEGIN_NAMESPACE	
#	define EXTL_INTELLIGENCE_END_NAMESPACE		
#endif

/* intelligence::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_INTELLIGENCE(x)						intelligence::x
#else 
#	define EXTL_NS_INTELLIGENCE(x)						x
#endif

/* ::extl::intelligence begin */
#define EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE			\
					EXTL_BEGIN_NAMESPACE 				\
					EXTL_INTELLIGENCE_BEGIN_NAMESPACE


/* ::extl::intelligence end */
#define EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE			\
					EXTL_INTELLIGENCE_END_NAMESPACE		\
					EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_CONFIG_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */
