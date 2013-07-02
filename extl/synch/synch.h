/* ///////////////////////////////////////////////////////////////////////
 * File:		synch.h		
 *
 * Created:		08.11.23					
 * Updated:		08.11.23
 *
 * Brief:		The Synchronization Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_SYNCH_H
#define EXTL_SYNCH_H

/*!\file synch.h
 * \brief The Synchronization library
 * \defgroup extl_group_synch
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "lock_base.h"
#include "null_lock.h"
#include "scoped_lock.h"
#ifndef EXTL_NEW_PLATFORM_ENABLE
#	include "synch_traits.h"
#	include "atomic_traits.h"
#endif
#include "synch_traits_selector.h"

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_SYNCH_H */
/* //////////////////////////////////////////////////////////////////// */
