/* ///////////////////////////////////////////////////////////////////////
 * File:		mpl.h		
 *
 * Created:		08.03.17				
 * Updated:		08.11.20
 *
 * Brief:		The Meta Programming Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MPL_H
#define EXTL_MPL_H

/*!\file mpl.h
 * \brief The mpl library
 * \defgroup extl_group_mpl
 */

#ifndef __cplusplus
#	error mpl.h need be supported by c++.
#endif

#ifndef EXTL_MPL_SUPPORT
#	error mpl.h is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical.h"
#include "bool_.h"
#include "int_.h"

#ifdef EXTL_MPL_IF_SUPPORT
#	include "if_.h"
#endif

#include "math/math.h"

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_H */
/* //////////////////////////////////////////////////////////////////// */

