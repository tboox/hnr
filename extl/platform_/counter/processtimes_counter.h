/* ///////////////////////////////////////////////////////////////////////
 * File:		processtimes_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		09.01.15
 *
 * Brief:		The processtimes_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_PROCESS_TIMES_COUNTER_H
#define EXTL_PLATFORM_PROCESS_TIMES_COUNTER_H

/*!\file processtimes_counter.h
 * \brief processtimes_counter class - precision: ms
 */
#ifndef __cplusplus
#	error processtimes_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#if defined(EXTL_PLATFORM_IS_UNIX)
#	include "../unix/counter/processtimes_counter.h"
#elif defined(EXTL_PLATFORM_IS_WINDOWS)
#	include "../windows/counter/processtimes_counter.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace
 */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE

// using windows/unix::highperformance_counter
EXTL_NS_USING_PLATFORM_SPEC(processtimes_counter)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace
 */
EXTL_PLATFORM_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_PROCESS_TIMES_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
