/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.02.02				
 * Updated:		08.04.15	
 *
 * Brief: Platform config
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONFIG_PLATFORM_H
#define EXTL_CONFIG_PLATFORM_H

#ifndef EXTL_CONFIG_H
#	error This file must be included of extl\config.h
#endif

/* Detecting platform */
#include "platform.h"

#if defined(EXTL_PLATFORM_IS_WIN)
#	include "win/config.h"

#elif defined(EXTL_PLATFORM_IS_UNIX)
#	include "unix/config.h"
#else
#	error Unknown platform.
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_PLATFORM_H */
/* //////////////////////////////////////////////////////////////////// */

