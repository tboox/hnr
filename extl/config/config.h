/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.02.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Library Configuration
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONFIG_H
#define EXTL_CONFIG_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "version.h"
#include "user/config.h"
#include "test.h"
#include "compiler/config.h"
#include "tchar.hpp"
#ifndef EXTL_NEW_PLATFORM_ENABLE
#	include "platform/config.h"
#endif
#include "stdlib/config.h"
#include "suffix.h"
#include "locale.hpp"

/* sub-library configuration */
#include "sub_config.h"

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_H */
/* //////////////////////////////////////////////////////////////////// */
