/* ///////////////////////////////////////////////////////////////////////
 * File:		synch_traits.h		
 *
 * Created:		08.05.15					
 * Updated:		08.05.15
 *
 * Brief:		synch_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SYNCH_SYNCH_TRAITS_H
#define EXTL_SYNCH_SYNCH_TRAITS_H

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
#include "atomic_traits.h"
#include "../platform/synch/lock_selector.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*\brief synch_traits class
 *
 * \param L The lock type
 * \param A The atomic traits type
 *
 * \ingroup extl_group_synch
 */
template<	typename_param_k L
		,	typename_param_k A
		>
struct synch_traits
{
	/// \name Types
	/// @{
	typedef L	lock_type;
	typedef A	atomic_traits_type;
	/// @}
};

/// Single thread synchronous traits 
typedef synch_traits<null_lock, atomic_traits<e_false_v> >							single_thread_synch_traits;

/// Multiple thread synchronous traits 
typedef synch_traits<	EXTL_NS_PLATFORM(lock_selector)::lock_type
					,	atomic_traits<e_true_v> 
					>																multi_thread_synch_traits;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_SYNCH_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
