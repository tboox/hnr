/* ///////////////////////////////////////////////////////////////////////
 * File:		synch_traits_selector.h		
 *
 * Created:		08.05.15					
 * Updated:		08.05.15
 *
 * Brief:	synchronous traits selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_SYNCH_SYNCH_TRAITS_SELECTOR_H
#define EXTL_SYNCH_SYNCH_TRAITS_SELECTOR_H

/*!\file synch_traits_selector.h
 * \brief synchronous traits selector
 */
#ifndef __cplusplus
#	error synch_traits_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#ifdef EXTL_NEW_PLATFORM_ENABLE
#	include "../platform_/synch/synch_traits.h"
#else
#	include "synch_traits.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief synch_traits_selector class
 *
 * \ingroup extl_group_synch
 */
#ifdef EXTL_NEW_PLATFORM_ENABLE
struct synch_traits_selector
{
#if defined(EXTL_SYNCH_TRAITS_SINGLE_THREAD)
	typedef EXTL_NS_PLATFORM(single_thread_synch_traits)	synch_traits_type;
#elif defined(EXTL_SYNCH_TRAITS_MULTI_THREAD)
	typedef EXTL_NS_PLATFORM(multi_thread_synch_traits)		synch_traits_type;
#else
#	error Unknown synch_traits.
#endif

};
#else
struct synch_traits_selector
{
#if defined(EXTL_SYNCH_TRAITS_SINGLE_THREAD)
	typedef single_thread_synch_traits						synch_traits_type;
#elif defined(EXTL_SYNCH_TRAITS_MULTI_THREAD)
	typedef multi_thread_synch_traits						synch_traits_type;
#else
#	error Unknown synch_traits.
#endif

};
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_SYNCH_TRAITS_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


