/* ///////////////////////////////////////////////////////////////////////
 * File:		intelligence.h		
 *
 * Created:		08.09.09
 * Updated:		08.09.09
 *
 * Brief:		The intelligence library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_H
#define EXTL_INTELLIGENCE_H

/*!\file intelligence.h
 * \brief The intelligence library
 * \defgroup extl_group_intelligence
 */

#ifndef __cplusplus
#	error intelligence.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "ga/ga.h"

#ifdef EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT
#	include "ann/ann.h"
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_H */
/* //////////////////////////////////////////////////////////////////// */
