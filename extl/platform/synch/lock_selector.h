/* ///////////////////////////////////////////////////////////////////////
 * File:		lock_selector.h		
 *
 * Created:		08.05.15					
 * Updated:		08.05.15
 *
 * Brief:	lock selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_SYNCH_LOCK_SELECTOR_H
#define EXTL_PLATFORM_SYNCH_LOCK_SELECTOR_H

#ifndef __cplusplus
#	error lock_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../platform.h"
#include "../../synch/null_lock.h"

#if defined(EXTL_PLATFORM_IS_WIN) && \
		!defined(EXTL_WIN_NO_SUPPORT)
#	include "../../win/synch/locks.h"

#elif defined(EXTL_PLATFORM_IS_UNIX) && \
		!defined(EXTL_UNIX_NO_SUPPORT)
#	error locks.h have not be implemented.
#else 
#	error Unknown Platform.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace 
 */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * [Description]
 * lock_selector class
 *
 * [Win Locks]
 * critical_section_lock
 * mutex_lock
 * semaphore_lock
 */
struct lock_selector
{
#if defined(EXTL_PLATFORM_IS_WIN)
	typedef critical_section_lock				lock_type;
#elif defined(EXTL_PLATFORM_IS_UNIX)
	typedef null_lock							lock_type;
#else
#	error Unknown Platform.
#endif

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace 
 */
EXTL_PLATFORM_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_SYNCH_LOCK_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


