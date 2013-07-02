/* ///////////////////////////////////////////////////////////////////////
 * File:		counter.h		
 *
 * Created:		08.11.24			
 * Updated:		08.11.24
 *
 * Brief:		The Windows Counter Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WINDOWS_COUNTER_H
#define EXTL_PLATFORM_WINDOWS_COUNTER_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "highperformance_counter.h"
#include "multimedia_counter.h"
#include "processtimes_counter.h"
#include "systemtime_counter.h"
#include "threadtimes_counter.h"
#include "tick_counter.h"

#ifdef EXTL_WINDOWS_COUNTER_RDTSC_COUNTER_SUPPORT
#	include "rdtsc_counter.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */

