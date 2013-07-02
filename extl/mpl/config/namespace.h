/* ///////////////////////////////////////////////////////////////////////
 * File:		namespace.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The MPL Library Namespace
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_CONFIG_NAMESPACE_H
#define EXTL_MPL_CONFIG_NAMESPACE_H

#ifndef EXTL_MPL_CONFIG_H
#	error This file must be included of extl\mpl\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * mpl namespace
 */
#ifndef	EXTL_NO_NAMESPACE
#	define EXTL_MPL_BEGIN_NAMESPACE				namespace mpl{
#	define EXTL_MPL_END_NAMESPACE				}
#else
#	define EXTL_MPL_BEGIN_NAMESPACE	
#	define EXTL_MPL_END_NAMESPACE		
#endif

/* mpl::x */
#if !defined(EXTL_NO_NAMESPACE)
#	define EXTL_NS_MPL(x)						mpl::x
#else 
#	define EXTL_NS_MPL(x)						x
#endif

/* ::extl::mpl begin */
#define EXTL_MPL_BEGIN_WHOLE_NAMESPACE	\
					EXTL_BEGIN_NAMESPACE	\
					EXTL_MPL_BEGIN_NAMESPACE 


/* ::extl::mpl end */
#define EXTL_MPL_END_WHOLE_NAMESPACE	\
					EXTL_MPL_END_NAMESPACE \
					EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_CONFIG_NAMESPACE_H */
/* //////////////////////////////////////////////////////////////////// */
