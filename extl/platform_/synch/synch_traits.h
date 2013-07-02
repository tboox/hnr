/* ///////////////////////////////////////////////////////////////////////
 * File:		synch_traits.h		
 *
 * Created:		08.05.15					
 * Updated:		09.01.15
 *
 * Brief:		the synch_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_SYNCH_TRAITS_H
#define EXTL_PLATFORM_SYNCH_TRAITS_H

/*!\file synch_traits.h
 * \brief synch_traits class
 * 
 * L = null_lock: Uses atomic functions 
 * L != null_lock: Uses lock
 */
#ifndef __cplusplus
#	error synch_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "atomic_traits.h"
#include "../../synch/null_lock.h"
#if defined(EXTL_PLATFORM_IS_UNIX)
#	include "../unix/synch/lock_selector.h"
#elif defined(EXTL_PLATFORM_IS_WINDOWS)
#	include "../windows/synch/lock_selector.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace 
 */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE 

/*\brief single_thread_synch_traits class
 *
 * \ingroup extl_group_synch
 */
struct single_thread_synch_traits
{
	/// \name Types
	/// @{
	typedef null_lock										lock_type;
	typedef atomic_traits<e_false_v>						atomic_traits_type;
	/// @}
};

/*\brief multi_thread_synch_traits class
 *
 * \ingroup extl_group_synch
 */
struct multi_thread_synch_traits
{
	/// \name Types
	/// @{
	typedef EXTL_NS_PLATFORM_SPEC(lock_selector)::lock_type		lock_type;
	typedef atomic_traits<e_true_v>								atomic_traits_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace 
 */
EXTL_PLATFORM_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_SYNCH_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
