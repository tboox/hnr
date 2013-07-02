/* ///////////////////////////////////////////////////////////////////////
 * File:		memory_traits_selector.h		
 *
 * Created:		08.07.30				
 * Updated:		08.07.30
 *
 * Brief: memory_traits_selector class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_MEMORY_TRAITS_SELECTOR_H
#define EXTL_MEMORY_MEMORY_TRAITS_SELECTOR_H

/*!\file memory_traits_selector.h
 * \brief memory_traits_selector class
 */
#ifndef __cplusplus
#	error memory_traits_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "object_memory_traits.h"
#include "pod_memory_traits.h"

#include "../type/traits/is_arithmetic.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "../type/traits/is_pod.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#	include "../type/traits/is_scalar.h"
#endif

#ifdef EXTL_MPL_IF_SUPPORT
#	include "../mpl/if_.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief memory_traits_selector class
 *
 * \param T The value type
 * 
 * \ingroup extl_group_memory
 */
template<typename_param_k T>
struct memory_traits_selector
{
	#ifdef EXTL_MPL_IF_SUPPORT
		#if defined(EXTL_TYPE_TRAITS_IS_POD_SUPPORT)
			typedef typename_type_k EXTL_NS_MPL(if_)<	(is_pod<T>::value)
													,	pod_memory_traits<T>
													,	object_memory_traits<T>
													>::type			memory_traits_type;

		#elif defined(EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT)
			typedef typename_type_k EXTL_NS_MPL(if_)<	(is_scalar<T>::value)
													,	pod_memory_traits<T>
													,	object_memory_traits<T>
													>::type			memory_traits_type;

		#else
			typedef typename_type_k EXTL_NS_MPL(if_)<	(is_arithmetic<T>::value)
													,	pod_memory_traits<T>
													,	object_memory_traits<T>
													>::type			memory_traits_type;
		#endif
	#else
		typedef object_memory_traits<T>								memory_traits_type;
	#endif
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_MEMORY_TRAITS_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */
