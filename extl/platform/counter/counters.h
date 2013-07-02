/* ///////////////////////////////////////////////////////////////////////
 * File:		counters.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.05
 *
 * Brief: Platform counters library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_COUNTERS_H
#define EXTL_PLATFORM_COUNTERS_H

#ifndef __cplusplus
#	error counters.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../platform.h"

/* ///////////////////////////////////////////////////////////////////////
 * Windows counters 
 */
#if defined(EXTL_PLATFORM_IS_WIN) && \
		!defined(EXTL_WIN_NO_SUPPORT)

#	ifndef EXTL_PLATFORM_WIN_TICK_COUNTER_H
#		include "../../win/counter/tick_counter.h"
#	endif

#	ifndef EXTL_PLATFORM_WIN_HIGH_PERFORMANCE_COUNTER_H
#		include "../../win/counter/highperformance_counter.h"
#	endif

#	ifndef EXTL_COMPILER_IS_GCC
#		ifndef EXTL_PLATFORM_WIN_MULTIMEDIA_COUNTER_H
#			include "../../win/counter/multimedia_counter.h"
#		endif
#	endif

#	ifndef EXTL_PLATFORM_WIN_SYSTEM_TIME_COUNTER_H
#		include "../../win/counter/systemtime_counter.h"
#	endif

/* Note: no accurate */
#	ifndef EXTL_PLATFORM_WIN_PROCESS_TIMES_COUNTER_H
#		include "../../win/counter/processtimes_counter.h"
#	endif

/* Note: no accurate */
#	ifndef EXTL_PLATFORM_WIN_THREAD_TIMES_COUNTER_H
#		include "../../win/counter/threadtimes_counter.h"
#	endif

#	if !defined(EXTL_PLATFORM_WIN_RDTSC_COUNTER_H) && \
			defined(EXTL_INLINE_ASM_IN_INLINE_SUPPORT) && \
				!defined(EXTL_COMPILER_IS_VECTORC)	/* VECTORC: no accurate */
#		include "../../win/counter/rdtsc_counter.h"
#	endif

/* Unix counters */
#elif defined(EXTL_PLATFORM_IS_UNIX) && \
	!defined(EXTL_UNIX_NO_SUPPORT)
#	error counter.h have not be implemented.
#else 
#	error Unknown Platform.
#endif 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_COUNTERS_H */
/* //////////////////////////////////////////////////////////////////// */
