/* ///////////////////////////////////////////////////////////////////////
 * File:		prefix.h		
 *
 * Created:		08.11.23					
 * Updated:		08.11.23
 *
 * Brief:		The Prefix File of The Extensible Template Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PREFIX_H
#define EXTL_PREFIX_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "config/config.h"
#include "utility/static_assert.h"
#include "utility/static_message_assert.h"
#include "type/type.h"

#ifndef EXTL_NEW_PLATFORM_ENABLE
#	include "platform/utility/assert.h"
#else
#	include "platform_/utility/assert.h"
#endif

#ifdef __cplusplus
#	include "log/log.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_PREFIX_H */
/* //////////////////////////////////////////////////////////////////// */
