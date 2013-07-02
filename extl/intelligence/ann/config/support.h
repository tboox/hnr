/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Artifical Neural Network Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_CONFIG_SUPPORT_H
#define EXTL_INTELLIGENCE_ANN_CONFIG_SUPPORT_H

#ifndef EXTL_INTELLIGENCE_ANN_CONFIG_H
#	error This file must be included of extl\intelligence\ann\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

// network support
#ifdef EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT
#	undef EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT
#endif

#ifdef EXTL_CONTAINER_NET_SUPPORT
#	define EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT
#endif

// ada-boosting networks support
#ifdef EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_NETWORKS_SUPPORT
#	undef EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_NETWORKS_SUPPORT
#endif

#if defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT) && \
		defined(EXTL_COMPILER_IS_GCC)
#	define EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_NETWORKS_SUPPORT
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
